/*******************************************************************************
* Helper functions for Validity driver interface functions
*
* This file contains the Helper functions for Validity driver interface functions
* and their definitions
*
* Copyright 2006  Validity Sensors, Inc.
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

#ifndef __vfsWrapper_h__
#define __vfsWrapper_h__


#define VFSW_RESULT_OK  0


enum vfs_matcher_type
{
	VFS_NT_MATCHER = 1,
	VFS_COGENT_MATCHER = 2,
	VFS_FPRINT_MATCHER = 3,
};

enum vfsw_capture_result
{
	VFSW_CAPTURE_ERROR = -1,
	VFSW_CAPTURE_COMPLETE = 1,
	VFSW_CAPTURE_FAIL
};

struct vfsw_data {
	void * pValidityCtx;
	void * hImage;
	void * pEnrollData;
};


int vfs_dev_init(struct vfsw_data *) __attribute__((nonnull));
int vfs_wait_for_service(void);
int vfs_set_matcher_type(enum vfs_matcher_type);
enum vfsw_capture_result vfs_capture(struct vfsw_data *, int) __attribute__((nonnull(1)));
int vfs_get_img_datasize(struct vfsw_data *) __attribute__((nonnull));
int vfs_get_img_width(struct vfsw_data *) __attribute__((nonnull));
int vfs_get_img_height(struct vfsw_data *) __attribute__((nonnull));
unsigned char * vfs_get_img_data(struct vfsw_data *) __attribute__((nonnull)) __attribute__ ((warn_unused_result));
void vfs_free_img_data(unsigned char *);
void vfs_clean_handles(struct vfsw_data *) __attribute__((nonnull));
void vfs_dev_exit(struct vfsw_data *) __attribute__((nonnull));


#endif /* __vfsWrapper_h__ */
