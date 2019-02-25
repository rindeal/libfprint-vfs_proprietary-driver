/*
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


#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif

#include "vfs_proprietary.h"
#include "drivers_api.h"
#include "capture_helper.h"
#include "assert.h"  /* ASSERT_* */
#include "trace.h"

#include <inttypes.h>  /* PRIu16 */

#include <glib.h>


/**
 * "random" number outside of the normal driver ID range, hopefully no conflicts will arise
 *
 * This ID should normally be placed in `libfprint/drivers/driver_ids.h`.
 */
#define VFS_PROPRIETARY_ID           65484
#define VFS_PROPRIETARY_FULLNAME     "Validity Sensors (proprietary driver)"
#define VFS_PROPRIETARY_NAME_RAW     vfs_proprietary
#define VFS_PROPRIETARY_NAME         G_STRINGIFY(VFS_PROPRIETARY_NAME_RAW)
#define VFS_PROPRIETARY_STRUCT_NAME  G_PASTE(VFS_PROPRIETARY_NAME_RAW, _driver)

#undef G_LOG_DOMAIN
#define G_LOG_DOMAIN  "libfprint-" VFS_PROPRIETARY_NAME

#undef ASSERT_PRINTF_CALL
#define ASSERT_PRINTF_CALL(_fmt_, ...) fp_err(_fmt_, ##__VA_ARGS__)
#undef ASSERT_GOTO_LABEL
#define ASSERT_GOTO_LABEL cleanup


/* img data callback needs to store multiple variables */
struct img_data_cb_user_data
{
	struct fp_img_dev * imgdev;
	struct fp_img * img;
};


static GString *
g_string_chomp (GString * const gstr)
{
	g_return_val_if_fail( gstr != NULL , NULL);

	while (G_LIKELY( gstr->len ))
	{
		if ( g_ascii_isspace((guchar) gstr->str[ gstr->len - 1 ]) )
			--gstr->len;
		else
			break;
	}

	gstr->str[ gstr->len ] = '\0';

	return gstr;
}

__attribute__((nonnull)) static int
vfs_proprietary_dev_open(struct fp_img_dev * const imgdev, unsigned long const driver_data)
{
	int retcode = -255;

	fpi_dev_set_nr_enroll_stages(FP_DEV(imgdev), VFS_PROPRIETARY_NR_ENROLL);

	retcode = 0;
	fpi_imgdev_open_complete(imgdev, retcode);

	return retcode;
}

__attribute__((nonnull)) static void
vfs_proprietary_dev_close(struct fp_img_dev * const imgdev)
{
	fpi_imgdev_close_complete(imgdev);
}

__attribute__((nonnull)) static int
ch_img_ready_callback(struct capture_helper_callback_args * args)
{
	TRACE();

	struct fp_img_dev * imgdev = args->user_data;

	g_assert_nonnull( imgdev );

	fpi_imgdev_report_finger_status(imgdev, TRUE);

	TRACE();

	return 0;
}

__attribute__((nonnull)) static int
ch_img_meta_callback(struct capture_helper_callback_args * args)
{
	TRACE();

	int retcode = -255;
	struct fp_img * img = NULL;

	struct capture_helper_img_metadata * imgmeta = args->payload.img_meta;
	struct fp_img * * img_p = args->user_data;

	g_assert_nonnull( imgmeta );
	g_assert_nonnull( img_p );

	ASSERT_PRINTF(
		imgmeta->len > 2 &&
		imgmeta->len <= VFS_PROPRIETARY_IMG_MAX_HEIGHT * VFS_PROPRIETARY_IMG_MAX_HEIGHT &&
		imgmeta->w > 0 && imgmeta->w <= VFS_PROPRIETARY_IMG_MAX_HEIGHT &&
		imgmeta->h > 0 && imgmeta->h <= VFS_PROPRIETARY_IMG_MAX_HEIGHT,
		-1, "Invalid img returned, w=%zu, h=%zu, len=%zu", imgmeta->w, imgmeta->h, imgmeta->len
	);

	img = fpi_img_new(imgmeta->len);
	ASSERT_PRINTF(img != NULL , -ENOMEM, "Could not get new fpi img");

	img->width = imgmeta->w;
	img->height = imgmeta->h;
	img->flags = FP_IMG_COLORS_INVERTED | FP_IMG_V_FLIPPED;

	fp_dbg("img: dimensions=%dx%d, length=%zu, flags=%" PRIu16,
			img->width, img->height, img->length, img->flags);

	imgmeta->data = img->data;
	*img_p = img;
	img = NULL;

	TRACE();

	retcode = 0;
cleanup:
	if (G_UNLIKELY( img != NULL ))
		fp_img_free(img);

	TRACE();

	return retcode;
}

__attribute__((nonnull)) static int
ch_img_data_callback(struct capture_helper_callback_args * args)
{
	TRACE();

	struct img_data_cb_user_data * user_data = args->user_data;

	fpi_imgdev_image_captured(user_data->imgdev, user_data->img);
	user_data->img = NULL;

	/* NOTE: finger off is expected only after submitting image... */
	fpi_imgdev_report_finger_status(user_data->imgdev, FALSE);

	TRACE();

	return 0;
}

__attribute__((nonnull)) static int
vfs_proprietary_dev_activate(
	struct fp_img_dev    * const imgdev,
	enum fp_imgdev_state   const state)
{
	fp_dbg("dev_activate(%d)", state);

	int interr, retcode = -255;

	struct capture_helper * ch = capture_helper_new();

	retcode = interr = capture_helper_spawn(ch);
	/* IMG_ACQUIRE_STATE_ACTIVATING => IMG_ACQUIRE_STATE_AWAIT_FINGER_ON */
	fpi_imgdev_activate_complete(imgdev, retcode);
	ASSERT_PRINTF( interr == 0 , retcode, "Failed to spawn capture-helper");

	struct img_data_cb_user_data img_data_cb_user_data = { .imgdev = imgdev, .img = NULL };

	capture_helper_callback_set(ch, CAPTURE_HELPER_CALLBACK_IMG_READY, ch_img_ready_callback, imgdev);
	capture_helper_callback_set(ch, CAPTURE_HELPER_CALLBACK_IMG_META, ch_img_meta_callback, &img_data_cb_user_data.img);
	capture_helper_callback_set(ch, CAPTURE_HELPER_CALLBACK_IMG_DATA, ch_img_data_callback, &img_data_cb_user_data);

	interr = capture_helper_wait_until_finished(ch);
	ASSERT_SILENT( interr == 0 , interr);

cleanup:
	if (G_UNLIKELY( retcode != 0 ))
	{
		capture_helper_stderr_try_read_all(ch);
		GString * stderr = capture_helper_stderr_get(ch);
		if (G_LIKELY( stderr->len ))
		{
			g_string_chomp(stderr);
			fp_err("capture-helper output:\n%.*s", (int) stderr->len, stderr->str);
		}
	}

	capture_helper_free(ch);

// 	if (G_UNLIKELY( retcode < 0 && fpi_dev_get_dev_state(FP_DEV(imgdev)) != DEV_STATE_ERROR ))
// 	{
// 		fpi_imgdev_session_error(imgdev, retcode);
// 	}

	if ( retcode < 0 )
		fp_dbg("dev_activate(): %s", strerror(-retcode));

	TRACE();

	return retcode;
}

__attribute__((nonnull)) static void
vfs_proprietary_dev_deactivate(struct fp_img_dev * imgdev)
{
	fpi_imgdev_deactivate_complete(imgdev);
}


static struct usb_id const
id_table[] = {
// 	{ .vendor = VALIDITY_VENDOR_ID, .product = VALIDITY_PRODUCT_ID_301,  },  // FOSS implementation exists
	{ .vendor = VALIDITY_VENDOR_ID, .product = VALIDITY_PRODUCT_ID_451,  },
// 	{ .vendor = VALIDITY_VENDOR_ID, .product = VALIDITY_PRODUCT_ID_5111, },  // FOSS implementation exists
// 	{ .vendor = VALIDITY_VENDOR_ID, .product = VALIDITY_PRODUCT_ID_5011, },  // FOSS implementation exists
	{ .vendor = VALIDITY_VENDOR_ID, .product = VALIDITY_PRODUCT_ID_471,  },
// 	{ .vendor = VALIDITY_VENDOR_ID, .product = VALIDITY_PRODUCT_ID_5131, },  // FOSS implementation exists
	{ .vendor = VALIDITY_VENDOR_ID, .product = VALIDITY_PRODUCT_ID_491,  },
	{ .vendor = VALIDITY_VENDOR_ID, .product = VALIDITY_PRODUCT_ID_495,  },
	{ 0 },
};

struct fp_img_driver
VFS_PROPRIETARY_STRUCT_NAME = {
	.driver = {
		.id = VFS_PROPRIETARY_ID,
		.name = VFS_PROPRIETARY_NAME,
		.full_name = VFS_PROPRIETARY_FULLNAME,
		.id_table = id_table,
		.scan_type = FP_SCAN_TYPE_SWIPE,
	},

	.open = vfs_proprietary_dev_open,
	.close = vfs_proprietary_dev_close,
	.activate = vfs_proprietary_dev_activate,
	.deactivate = vfs_proprietary_dev_deactivate,
};
