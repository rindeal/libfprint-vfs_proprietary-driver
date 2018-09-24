/*******************************************************************************
 * Copyright 2016, 2018  Jan Chren (rindeal)
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

#include "api.h"
#include "vfsFprintWrapper.h"
#include "../assert.h"
#include "../likely.h"
#include "../min_max.h"

#include <stdio.h>   /* fprintf, perror, fclose */
#include <stdlib.h>  /* exit */
#include <string.h>  /* strlen */
#include <stdbool.h>
#include <stdarg.h>  /* va_list, va_start, vfprintf, va_end */
#include <time.h>  /* time */

#include <signal.h>  /* signal */
#include <unistd.h>  /* alarm, write, close */
#include <syslog.h>  /* openlog, syslog */
#include <errno.h>   /* errno, E* */


#undef ASSERT_RETCODE_VARIABLE_NAME
#define ASSERT_RETCODE_VARIABLE_NAME  exit_code

#define ASSERT_VFSW_RESULT_OK(_res_, _retcode_, _func_)  \
	ASSERT_PRINTF((_res_) == VFSW_RESULT_OK, _retcode_, "%s() => %d", (_func_), (_res_))

#define EXECUTE_IN_TIME(_sec_, _msg_, _body_)  \
	g_sigalrm_msg = (_msg_);                   \
	alarm(MIN(MAX(VFS_PROPRIETARY_CAPTURE_HELPER_TIMEOUT - (time(NULL) - startup), 0), (_sec_))); \
	_body_                                     \
	alarm(0)


static const char * g_sigalrm_msg = "";


/***
 * prevent libvfsFprintWrapper from spamming syslog
 */
static const char * g_syslog_ident = "";
void
openlog(const char * ident, int option, int facility)
{
	g_syslog_ident = ident;
	return;
}
void
syslog(int priority, const char *format, ...)
{
	fprintf(stderr, "syslog: %s: ", g_syslog_ident);

	va_list ap;
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	return;
}


__attribute__ ((noreturn)) static void
sigalrm_handler(int const sig)
{
	alarm(0);

	if ( g_sigalrm_msg != NULL && g_sigalrm_msg[0] != '\0' )
	{
		fprintf(stderr, "SIGALRM caught: %s\n", g_sigalrm_msg);
	}

	exit(ETIMEDOUT);
}


int
main(int const argc, char * const argv[])
{
	int exit_code = EXIT_FAILURE;
	int iretval;
	time_t startup = time(NULL);

	struct capture_helper_api_input  ipcin  = { 0 };
	struct capture_helper_api_img_metadata imgmeta = { 0 };

	bool vfs_initialized = false;
	struct vfsw_data vfsw_data = { 0 };
	unsigned char * vfsw_img_data = NULL;

	ASSERT_PERROR( signal(SIGALRM, sigalrm_handler) != SIG_ERR ,
					errno, "Failed to setup signal handler");


	iretval = read(STDIN_FILENO, &ipcin, sizeof(ipcin));
	ASSERT_PERROR( iretval == sizeof(ipcin) , errno, "Failed to read IPC in");
	fclose(stdin);


	EXECUTE_IN_TIME(1, "timed out waiting for VFS service",
		iretval = vfs_wait_for_service();
		ASSERT_VFSW_RESULT_OK(iretval, EXIT_FAILURE, "vfs_wait_for_service");
	);
	EXECUTE_IN_TIME(2, "timed out waiting for VFS wrapper to initialize",
		iretval = vfs_set_matcher_type(VFS_FPRINT_MATCHER);
		ASSERT_VFSW_RESULT_OK(iretval, EXIT_FAILURE, "vfs_set_matcher_type");

		/*
		 * vfs_dev_init() can fail and block the execution forever.
		 * gdb says it locks itself up when writing to a pipe which it uses
		 * for communication with vcsFPService.
		 *
		 * The lockup can be triggered by `kill -9`ing application waiting on vfs_capture().
		 *
		 * It takes about 0.4s to execute.
		 *
		 * This function also prints messages like:
		 *
		 *     Sensor usb#vid_138a#pid_003f#... plugged.
		 *
		 */
		iretval = vfs_dev_init(&vfsw_data);
		ASSERT_VFSW_RESULT_OK(iretval, EXIT_FAILURE, "vfs_dev_init");
	);
	vfs_initialized = true;


	EXECUTE_IN_TIME(VFS_PROPRIETARY_CAPTURE_HELPER_TIMEOUT, "Timed out waiting for capture",
		/* this will fail if some other instance tries the same while we're waiting for swipe */
		iretval = vfs_capture(&vfsw_data, 1);
		ASSERT_PRINTF( iretval == VFSW_CAPTURE_COMPLETE , EXIT_FAILURE, "Could not capture fingerprint");
	);


	EXECUTE_IN_TIME(1, "Timed out waiting for data to be passed to parent",
		struct capture_helper_api_img_ready const img_is_ready = { .status = CAPTURE_HELPER_IMG_READY_OK };
		ASSERT_PERROR(
			write(ipcin.img_ready_fd, &img_is_ready, sizeof(img_is_ready)) == sizeof(img_is_ready),
			errno, "Failed to announce img ready status"
		);
		close(ipcin.img_ready_fd);

		vfsw_img_data = vfs_get_img_data(&vfsw_data);
		imgmeta.img_len = vfs_get_img_datasize(&vfsw_data);
		imgmeta.img_w = vfs_get_img_width(&vfsw_data);
		imgmeta.img_h = vfs_get_img_height(&vfsw_data);
		ASSERT_PRINTF( vfsw_img_data != NULL && imgmeta.img_len > 0 , EXIT_FAILURE, "Empty image captured");

		ASSERT_PERROR(
			write(ipcin.img_meta_fd, &imgmeta, sizeof(imgmeta)) == sizeof(imgmeta),
			errno, "Failed to write IPC out"
		);
		close(ipcin.img_meta_fd);

		ASSERT_PERROR(
			write(ipcin.img_data_fd, vfsw_img_data, imgmeta.img_len) == imgmeta.img_len,
			errno, "Failed to write image data"
		);
		close(ipcin.img_data_fd);
	);


	exit_code = EXIT_SUCCESS;

cleanup:
	/* disarm pending alarm if any */
	alarm(0);

	if ( vfs_initialized )
	{
		EXECUTE_IN_TIME(2, "failed to cleanup vfs",
			if ( vfsw_img_data != NULL )
			{
				vfs_free_img_data(vfsw_img_data);
			}

			vfs_clean_handles(&vfsw_data);
			vfs_dev_exit(&vfsw_data);
		);
	}

	return exit_code;
}
