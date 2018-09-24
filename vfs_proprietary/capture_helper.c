/*******************************************************************************
 * Copyright 2018  Jan Chren (rindeal)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif

#include "capture_helper.h"
#include "capture-helper/api.h"
#include "vfs_proprietary.h"
#include "drivers_api.h"
#include "assert.h"                   /* ASSERT_* */
#include "trace.h"
#include "union_of_struct_n_array.h"  /* UNION_OF_STRUCT_N_ARRAY */

#include <errno.h>     /* errno */
#include <stddef.h>    /* size_t, NULL */
#include <stdio.h>     /* BUFSIZ */
#include <stdbool.h>
#include <string.h>    /* memset, strerror */

#include <unistd.h>    /* STDOUT_FILENO, STDERR_FILENO, pipe, read, write, close */
#include <spawn.h>     /* posix_spawn* */
#include <sys/wait.h>  /* waitpid */
#include <fcntl.h>     /* O_* */
#include <signal.h>    /* kill */
#include <sys/epoll.h> /* epoll_* */
#include <sys/time.h>  /* struct timeval */
#include <sys/types.h> /* pid_t */

#include <glib.h>


#undef G_LOG_DOMAIN
#define G_LOG_DOMAIN  "libfprint-" "capture-helper"

#undef ASSERT_PRINTF_CALL
#define ASSERT_PRINTF_CALL(_fmt_, ...) fp_err(_fmt_, ##__VA_ARGS__)
#undef ASSERT_GOTO_LABEL
#define ASSERT_GOTO_LABEL cleanup


typedef int
(*capture_helper_epoll_eevh_t)(
	struct capture_helper    * ch,
	const struct epoll_event * eev
);

UNION_OF_STRUCT_N_ARRAY(
	pipe,,
	,,
	a,
	int,
	r, w
);

enum efd
{
	EFD_STDERR = 0,
	EFD_IMG_READY,
	EFD_IMG_META,
	EFD_IMG_DATA,
	_EFD_LAST_,
};

struct capture_helper
{
	time_t startup;
	pid_t pid;
	int wstatus;

	int epollfd;
	/* the number of registered file descriptors - the event loop won't end unless this becomes zero again */
	size_t epoll_nreg;
	int efds[_EFD_LAST_];
	struct
	{
		capture_helper_callback_t cb;
		void * user_data;
	} callbacks[_CAPTURE_HELPER_CALLBACK_LAST_];

	GString * stderr;

	struct
	{
		unsigned char * buf;
		size_t          bufsz;
		size_t          used;
	} img_data;
};


static capture_helper_epoll_eevh_t const epoll_event_handlers[];


__attribute__((nonnull)) static void
close_and_invalidate(int * fd)
{
	if ( *fd < 0 )
		return;

	(void) close(*fd);
	*fd = -1;
}


struct capture_helper *
capture_helper_new(void)
{
	struct capture_helper * ch = g_malloc0(sizeof(struct capture_helper));

	ch->epollfd = -1;
	for ( size_t i = 0; i < G_N_ELEMENTS(ch->efds); i++)
		ch->efds[i] = -1;

	ch->stderr = g_string_sized_new(65536);

	return ch;
}

void
capture_helper_free(struct capture_helper * ch)
{
	close_and_invalidate(&ch->epollfd);

	for ( size_t i = 0; i < G_N_ELEMENTS(ch->efds); i++ )
		close_and_invalidate(ch->efds + i);

	g_string_free(ch->stderr, TRUE);

	if ( ch->pid > 0 )
	{
		fp_dbg("Killing capture-helper");
		kill(ch->pid, SIGKILL);
		waitpid(ch->pid, &ch->wstatus, WNOHANG);
	}

	g_free(ch);
}


int
capture_helper_spawn(struct capture_helper * ch)
{

	int interr, retcode = -255;
	size_t i;
	union {
		struct __attribute__ ((__packed__))
		{
			/**
			 * pipes we want to read from
			 */
			UNION_OF_STRUCT_N_ARRAY(
				, r,
				,,
				a,
				union pipe,
				stderr, img_ready, img_meta, img_data
			);
			/**
			 * pipes we want to write to
			 */
			UNION_OF_STRUCT_N_ARRAY(
				, w,
				,,
				a,
				union pipe,
				stdin
			);
		};
		union pipe a[0];
	} pipes;
	const size_t npipes = sizeof(pipes) / sizeof(union pipe);
	for ( i = 0; i < npipes; i++ )
		pipes.a[i] = (union pipe){ .r = -1, .w = -1 };

	pid_t pid = -1;
	posix_spawn_file_actions_t spawn_actions
		__attribute__((cleanup(posix_spawn_file_actions_destroy)));
	posix_spawn_file_actions_init(&spawn_actions);
	posix_spawnattr_t spawn_attrs
		__attribute__((cleanup(posix_spawnattr_destroy)));
	posix_spawnattr_init(&spawn_attrs);


	for ( i = 0; i < npipes; i++ )
	{
		ASSERT_PERROR( pipe(pipes.a[i].a) == 0 , -errno, "Failed to create pipes");
	}
	for ( i = 0; i < G_N_ELEMENTS(pipes.r.a); i++ )
	{
		ASSERT_PERROR(
			fcntl(pipes.r.a[i].r, F_SETFL, O_NONBLOCK) != -1 &&
			fcntl(pipes.r.a[i].r, F_SETFD, O_CLOEXEC) != -1,
			-errno, "Failed to fcntl r pipes"
		);
	}
	for ( i = 0; i < G_N_ELEMENTS(pipes.w.a); i++ )
	{
		ASSERT_PERROR(
			fcntl(pipes.w.a[i].w, F_SETFL, O_NONBLOCK) != -1 &&
			fcntl(pipes.w.a[i].w, F_SETFD, O_CLOEXEC) != -1,
			-errno, "Failed to fcntl w pipes"
		);
	}
	ASSERT_PERROR(
		fcntl(pipes.w.stdin.w, F_SETPIPE_SZ, sizeof(struct capture_helper_api_input)) != -1 &&
		fcntl(pipes.r.img_ready.r, F_SETPIPE_SZ, sizeof(struct capture_helper_api_img_ready)) != -1 &&
		fcntl(pipes.r.img_meta.r, F_SETPIPE_SZ, sizeof(struct capture_helper_api_img_metadata)) != -1,
		-errno, "Failed to set pipe sizes"
	);


	ASSERT_STRERROR(
		( interr = posix_spawn_file_actions_adddup2(&spawn_actions, pipes.w.stdin.r, STDIN_FILENO) ) == 0 &&
		( interr = posix_spawn_file_actions_adddup2(&spawn_actions, pipes.r.stderr.w, STDOUT_FILENO) ) == 0 &&
		( interr = posix_spawn_file_actions_adddup2(&spawn_actions, pipes.r.stderr.w, STDERR_FILENO) ) == 0,
		interr, -interr, "Failed to initialize posix_spawn"
	);

	char * empty_str_list[] = { NULL };
	interr = posix_spawn(&pid, VFS_PROPRIETARY_CAPTURE_HELPER_PATH,
							&spawn_actions, &spawn_attrs, empty_str_list, empty_str_list);
	ASSERT_PERROR( interr == 0 , -errno, "Failed to spawn capture-helper");
	fp_dbg("capture-helper spawned successfully, pid=%d", pid);
	ch->startup = time(NULL);


	struct capture_helper_api_input api_in = {
		.img_ready_fd = pipes.r.img_ready.w,
		.img_meta_fd = pipes.r.img_meta.w,
		.img_data_fd = pipes.r.img_data.w,
	};
	ASSERT_PERROR(
		write(pipes.w.stdin.w, &api_in, sizeof(api_in)) == sizeof(api_in),
		-errno, "Failed to pass IPC FD to child"
	);
	close(pipes.w.stdin.w);


	ch->pid = pid;
	ch->efds[EFD_STDERR]    = pipes.r.stderr.r;
	ch->efds[EFD_IMG_READY] = pipes.r.img_ready.r;
	ch->efds[EFD_IMG_META]  = pipes.r.img_meta.r;
	ch->efds[EFD_IMG_DATA]  = pipes.r.img_data.r;


	retcode = 0;
cleanup:
	for ( i = 0; i < G_N_ELEMENTS(pipes.r.a); i++ )
		close(pipes.r.a[i].w);
	for ( i = 0; i < G_N_ELEMENTS(pipes.w.a); i++ )
		close(pipes.w.a[i].r);

	if (G_UNLIKELY( retcode != 0 ))
	{
		for ( i = 0; i < G_N_ELEMENTS(pipes.r.a); i++ )
			close(pipes.r.a[i].r);
		for ( i = 0; i < G_N_ELEMENTS(pipes.w.a); i++ )
			close(pipes.w.a[i].w);

		if ( pid > 0 )
			kill(pid, SIGKILL);
	}

	return retcode;
}


GString *
capture_helper_stderr_get (struct capture_helper * ch)
{
	return ch->stderr;
}

/* return 0 when EOF, 1 when EAGAIN, otherwise <0 */
int
capture_helper_stderr_try_read_all (struct capture_helper * const ch)
{
	if (G_UNLIKELY( ch->efds[EFD_STDERR] < 0 ))
		return -EBADF;

	g_assert( fcntl(ch->efds[EFD_STDERR], F_GETFL) & O_NONBLOCK );

	char buf[BUFSIZ];
	ssize_t bytes_read;

	do
 	{
		errno = 0;
		bytes_read = read(ch->efds[EFD_STDERR], buf, G_N_ELEMENTS(buf));
		if ( bytes_read > 0 )
		{
			g_string_append_len(ch->stderr, buf, bytes_read);
		}
		/* EOF */
		else if ( bytes_read == 0 )
		{
			return 0;
		}
		/* EAGAIN */
		else if ( bytes_read == -1 && errno == EAGAIN )
		{
			return 1;
		}
		/* error */
		else
		{
			return ( errno <= 0 || errno > 255 ) ? -255 : -errno;
		}
	} while(1);
}


__attribute__((nonnull)) static int
capture_helper_epoll_register (struct capture_helper * const ch, enum efd efd, int const events)
{
	int interr, retcode = -255;
	struct epoll_event ev = {
		.events = events,
		.data.u64 = efd,
	};

	ASSERT_PRINTF( ch->epoll_nreg < _EFD_LAST_ , -1, "%s: epoll_nreg (==%zu) already reached maximum %d",
					__func__, ch->epoll_nreg, _EFD_LAST_ - 1);

	interr = epoll_ctl(ch->epollfd, EPOLL_CTL_ADD, ch->efds[efd], &ev);
	ASSERT_PERROR( interr == 0 , -errno, "EPOLL_CTL_ADD");

	ch->epoll_nreg++;

	retcode = 0;
cleanup:
	return retcode;
}

__attribute__((nonnull)) static int
capture_helper_epoll_unregister (struct capture_helper * ch, enum efd efd)
{
	int interr, retcode = -255;

	ASSERT_PRINTF( ch->epoll_nreg != 0 , -1, "%s: epoll_nreg == 0!", __FUNCTION__);

	interr = epoll_ctl(ch->epollfd, EPOLL_CTL_DEL, ch->efds[efd], NULL);
	ASSERT_PERROR( interr == 0 , -errno, "EPOLL_CTL_DEL");

	ch->epoll_nreg--;

	retcode = 0;
cleanup:
	return retcode;
}

int
capture_helper_epoll_handle_event (
	struct capture_helper * const ch,
	const struct epoll_event * const ev)
{
	enum efd efd = (enum efd) ev->data.u64;

	g_assert( efd >= 0 );
	g_assert( efd < _EFD_LAST_ );

	return epoll_event_handlers[efd](ch, ev);
}


void
capture_helper_callback_set (
	struct capture_helper * ch,
	enum capture_helper_callback_types cb_type,
	capture_helper_callback_t cb,
	void * user_data)
{
	g_assert(cb_type >= 0);
	g_assert(cb_type < _CAPTURE_HELPER_CALLBACK_LAST_);

	ch->callbacks[cb_type].cb = cb;
	ch->callbacks[cb_type].user_data = user_data;
}

__attribute__((nonnull)) static int
capture_helper_callback_call (
	struct capture_helper * ch,
	enum capture_helper_callback_types cb_type,
	struct capture_helper_callback_args * args)
{
	g_assert(cb_type >= 0);
	g_assert(cb_type < _CAPTURE_HELPER_CALLBACK_LAST_);

	capture_helper_callback_t cb = ch->callbacks[cb_type].cb;
	if (G_UNLIKELY( cb == NULL ))
		return 1;

	args->ch = ch;
	args->user_data = ch->callbacks[cb_type].user_data;

	return cb(args);
}


#define CAPTURE_HELPER_REMAINING_TIME(_ch_p_) ( VFS_PROPRIETARY_CAPTURE_HELPER_TIMEOUT - ( time(NULL) - (_ch_p_)->startup ) )

int
capture_helper_wait_until_finished(struct capture_helper * const ch)
{
	int interr, retcode = -255;

	ch->epollfd = epoll_create1(EPOLL_CLOEXEC);
	ASSERT_PERROR( ch->epollfd != -1 , -errno, "Failed to create epoll");

	interr = capture_helper_epoll_register(ch, EFD_STDERR, EPOLLIN);
	ASSERT_PRINTF( interr == 0 , -errno, "Failed to register stderr to epoll");

	interr = capture_helper_epoll_register(ch, EFD_IMG_READY, EPOLLIN);
	ASSERT_PRINTF( interr == 0 , -errno, "Failed to register img_ready to epoll");

	fp_dbg("entering epoll loop");
	while ( ch->epoll_nreg )
	{
		struct epoll_event eev;

		int timeout = CAPTURE_HELPER_REMAINING_TIME(ch) * 1000;
		ASSERT_PRINTF( timeout > 0 , -ETIMEDOUT, "Timed out waiting for capture-helper");

		interr = epoll_wait(ch->epollfd, &eev, 1, timeout);
		ASSERT_PERROR( interr != -1 , -errno, "epoll_wait");

		if ( interr == 0 )
			/* timeout expired, just restart loop */
			continue;

		interr = capture_helper_epoll_handle_event(ch, &eev);
		ASSERT_SILENT( interr == 0 , interr);
	}

	interr = waitpid(ch->pid, &ch->wstatus, WNOHANG);
	ASSERT_PERROR( interr != -1 , -errno, "waitpid");
	ASSERT_PRINTF( interr != 0 , -1, "waitpid: child not dead yet");
	ch->pid = -1;

	retcode = -WEXITSTATUS(ch->wstatus);
	ASSERT_PRINTF( WIFEXITED(ch->wstatus) , retcode, "capture-helper exit code: %d", WEXITSTATUS(ch->wstatus));

cleanup:

	return retcode;
}


__attribute__((nonnull)) static int
capture_helper_eevh_stderr (
	      struct capture_helper * const ch,
	const struct epoll_event *    const ev)
{
	g_assert( (enum efd) ev->data.u64 == EFD_STDERR );

	int interr, retcode = -255;

	if ( ev->events & EPOLLIN )
	{
		interr = capture_helper_stderr_try_read_all(ch);
		ASSERT_PERROR( interr >= 0 , interr, "Failed to read capture-helper stderr");

		if ( interr > 0 )
			return 0;
	}

	retcode = 0;
cleanup:
	interr = capture_helper_epoll_unregister(ch, EFD_STDERR);
	if (G_UNLIKELY( interr != 0 ))
	{
		fp_err("Failed to unregister stderr from epoll");
		if ( retcode == 0 )
			retcode = interr;
	}
	close_and_invalidate(ch->efds + EFD_STDERR);

	return retcode;
}

__attribute__((nonnull)) static int
capture_helper_eevh_imgready (
	      struct capture_helper * const ch,
	const struct epoll_event *    const eev)
{
	g_assert( (enum efd) eev->data.u64 == EFD_IMG_READY );

	int interr, retcode = -255;

	ASSERT_PRINTF( eev->events & EPOLLIN , -ECONNABORTED,
					"capture-helper probably died while we were waiting for img ready signal");


	struct capture_helper_api_img_ready api_img_ready = { .status = 0 };
	ASSERT_PERROR(
		read(ch->efds[EFD_IMG_READY], &api_img_ready, sizeof(api_img_ready)) == sizeof(api_img_ready),
		-errno, "Failed to ready img ready status"
	);
	ASSERT_PRINTF( api_img_ready.status == CAPTURE_HELPER_IMG_READY_OK , -254, "Invalid img ready status read");


	struct capture_helper_callback_args cb_args = {
		.payload.img_ready = NULL
	};
	interr = capture_helper_callback_call(ch, CAPTURE_HELPER_CALLBACK_IMG_READY, &cb_args);
	ASSERT_PRINTF( interr >= 0 , -254, "imgready cb call failed");


	ASSERT_SILENT( ( retcode = capture_helper_epoll_register(ch, EFD_IMG_META, EPOLLIN) ) == 0 , retcode);


	retcode = 0;
cleanup:
	interr = capture_helper_epoll_unregister(ch, EFD_IMG_READY);
	if (G_UNLIKELY( interr != 0 ))
	{
		fp_err("Failed to unregister stderr from epoll");
		if ( retcode == 0 )
			retcode = interr;
	}
	close_and_invalidate(ch->efds + EFD_IMG_READY);

	return retcode;
}

__attribute__((nonnull)) static int
capture_helper_eevh_imgmeta (
	      struct capture_helper * const ch,
	const struct epoll_event *    const eev)
{
	g_assert( (enum efd) eev->data.u64 == EFD_IMG_META );

	int interr, retcode = -255;

	ASSERT_PRINTF( eev->events & EPOLLIN , -ECONNABORTED,
					"capture-helper probably died while we were waiting for img metadata");


	struct capture_helper_api_img_metadata api_payload;
	ASSERT_PERROR(
		read(ch->efds[EFD_IMG_META], &api_payload, sizeof(api_payload)) == sizeof(api_payload),
		-errno, "Failed to ready img ready status"
	);


	struct capture_helper_img_metadata imgmeta = {
		.w = api_payload.img_w,
		.h = api_payload.img_h,
		.len = api_payload.img_len,
		.data = NULL,
	};
	struct capture_helper_callback_args cb_args = {
		.payload.img_meta = &imgmeta
	};
	interr = capture_helper_callback_call(ch, CAPTURE_HELPER_CALLBACK_IMG_META, &cb_args);
	ASSERT_PRINTF( interr >= 0 , -254, "imgmeta cb call failed");
	ASSERT_PRINTF( imgmeta.data != NULL , -1, "imgmeta cb didn't fill 'data' field");


	ch->img_data.buf = imgmeta.data;
	ch->img_data.bufsz = imgmeta.len;


	ASSERT_SILENT( ( retcode = capture_helper_epoll_register(ch, EFD_IMG_DATA, EPOLLIN) ) == 0 , retcode);


	retcode = 0;
cleanup:
	interr = capture_helper_epoll_unregister(ch, EFD_IMG_META);
	if (G_UNLIKELY( interr != 0 ))
	{
		fp_err("Failed to unregister stderr from epoll");
		if ( retcode == 0 )
			retcode = interr;
	}
	close_and_invalidate(ch->efds + EFD_IMG_META);

	return retcode;
}

__attribute__((nonnull)) static int
capture_helper_eevh_imgdata (
	      struct capture_helper * const ch,
	const struct epoll_event *    const eev)
{
	g_assert( (enum efd) eev->data.u64 == EFD_IMG_DATA );
	g_assert_nonnull( ch->img_data.buf );
	g_assert_cmpuint(ch->img_data.bufsz, >, ch->img_data.used);

	int interr, retcode = -255;
	size_t bytes_remaining = ch->img_data.bufsz - ch->img_data.used;

	ASSERT_PRINTF( eev->events & EPOLLIN , -ECONNABORTED,
					"capture-helper probably died while we were waiting for img data");


	ASSERT_PERROR(
		(interr = read(ch->efds[EFD_IMG_DATA], ch->img_data.buf + ch->img_data.used, bytes_remaining)) > 0,
		-errno, "Failed to read img data"
	);
	ch->img_data.used += interr;


	if ( ch->img_data.used < ch->img_data.bufsz )
		return 0;


	struct capture_helper_callback_args cb_args = {
		.payload.img_data = ch->img_data.buf,
	};
	interr = capture_helper_callback_call(ch, CAPTURE_HELPER_CALLBACK_IMG_DATA, &cb_args);
	ASSERT_PRINTF( ! ( interr < 0 ) , -1, "imgdata cb call failed");


	/* img data are out of our control as of now, cleanup their traces immediately to prevent accidentical usage */
	memset(&ch->img_data, 0, sizeof(ch->img_data));


	retcode = 0;
cleanup:
	interr = capture_helper_epoll_unregister(ch, EFD_IMG_DATA);
	if (G_UNLIKELY( interr != 0 ))
	{
		fp_err("Failed to unregister stderr from epoll");
		if ( retcode == 0 )
			retcode = interr;
	}
	close_and_invalidate(ch->efds + EFD_IMG_DATA);

	return retcode;
}


static capture_helper_epoll_eevh_t const
epoll_event_handlers[_EFD_LAST_] = {
	[EFD_STDERR] = capture_helper_eevh_stderr,
	[EFD_IMG_READY] = capture_helper_eevh_imgready,
	[EFD_IMG_META] = capture_helper_eevh_imgmeta,
	[EFD_IMG_DATA] = capture_helper_eevh_imgdata,
};
