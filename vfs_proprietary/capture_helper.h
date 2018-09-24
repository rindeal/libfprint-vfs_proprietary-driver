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

#include <glib.h>  /* GString */


#ifndef VFS_PROPRIETARY_CAPTURE_HELPER_PATH
# define VFS_PROPRIETARY_CAPTURE_HELPER_PATH "capture-helper"
#endif


struct capture_helper;

struct capture_helper_img_metadata
{
	size_t w;
	size_t h;
	size_t len;

	unsigned char * data;
};


enum capture_helper_callback_types
{
	CAPTURE_HELPER_CALLBACK_IMG_READY = 0,
	CAPTURE_HELPER_CALLBACK_IMG_META,
	CAPTURE_HELPER_CALLBACK_IMG_DATA,
	_CAPTURE_HELPER_CALLBACK_LAST_
};

struct capture_helper_callback_args
{
	struct capture_helper * ch;
	union
	{
		void * img_ready;  /* NULL */
		struct capture_helper_img_metadata * img_meta;
		unsigned char * img_data;
	} payload;
	void * user_data;
};

typedef int (*capture_helper_callback_t)(struct capture_helper_callback_args *);


struct capture_helper *
capture_helper_new (void)
	__attribute__((visibility("hidden")));
void
capture_helper_free (struct capture_helper *)
	__attribute__((nonnull)) __attribute__((visibility("hidden")));

void
capture_helper_callback_set (struct capture_helper *, enum capture_helper_callback_types, capture_helper_callback_t, void *)
	__attribute__((nonnull(1))) __attribute__((visibility("hidden")));

int
capture_helper_spawn (struct capture_helper *)
	__attribute__((nonnull)) __attribute__((visibility("hidden")));
int
capture_helper_wait_until_finished (struct capture_helper *)
	__attribute__((nonnull)) __attribute__((visibility("hidden")));

int
capture_helper_stderr_try_read_all (struct capture_helper *)
	__attribute__((nonnull)) __attribute__((visibility("hidden")));
GString *
capture_helper_stderr_get (struct capture_helper *)
	__attribute__((nonnull)) __attribute__((returns_nonnull))
	__attribute__((visibility("hidden")));
