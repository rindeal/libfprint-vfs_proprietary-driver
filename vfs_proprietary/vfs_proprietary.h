/**
 * Copyright 2006  Validity Sensors, Inc.
 * Copyright 2016,2018  Jan Chren (rindeal)
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

#ifndef VFS_PROPRIETARY_H_
#define VFS_PROPRIETARY_H_


#define VALIDITY_VENDOR_ID          0x138A
// #define VALIDITY_PRODUCT_ID_301     0x0005  // FLOSS implementation exists
#define VALIDITY_PRODUCT_ID_451     0x0007
#define VALIDITY_PRODUCT_ID_471     0x003c
#define VALIDITY_PRODUCT_ID_491     0x003d
#define VALIDITY_PRODUCT_ID_495     0x003f
// #define VALIDITY_PRODUCT_ID_5011    0x0011  // FLOSS implementation exists
// #define VALIDITY_PRODUCT_ID_5111    0x0010  // FLOSS implementation exists
// #define VALIDITY_PRODUCT_ID_5131    0x0018  // FLOSS implementation exists

/* Minimum image height */
// #define VFS_PROPRIETARY_IMG_MIN_HEIGHT  200  // less than 200 returned when run-testing

/* Maximum image height */
#define VFS_PROPRIETARY_IMG_MAX_HEIGHT  1023  // not used originally

/* Number of enroll stages */
#define VFS_PROPRIETARY_NR_ENROLL       1

// #define VAL_MIN_ACCEPTABLE_MINUTIAE (2*MIN_ACCEPTABLE_MINUTIAE)  // not used
// #define VAL_DEFAULT_THRESHOLD 60  // not used

// #define VCS_MAX_FINGER              10  // not used
// #define MAX_ENROLLMENT_PRINTS       3  // not used
// #define MAX_TEMPLATES               10  // not used


#endif /* VFS_PROPRIETARY_H_ */
