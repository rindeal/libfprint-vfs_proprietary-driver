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

#ifndef VFS_PROPRIETARY_ASSERT_H_
#define VFS_PROPRIETARY_ASSERT_H_


#include "likely.h"


#ifndef ASSERT_PRINTF_CALL
#  define ASSERT_PRINTF_CALL(_fmt_, ...)  fprintf(stderr, _fmt_ "\n", ##__VA_ARGS__)
#endif
#ifndef ASSERT_GOTO_LABEL
#  define ASSERT_GOTO_LABEL cleanup
#endif
#ifndef ASSERT_RETCODE_VARIABLE_NAME
#  define ASSERT_RETCODE_VARIABLE_NAME  retcode
#endif
#ifndef ASSERT_ADDITIONAL_FAILURE_CODE
#  define ASSERT_ADDITIONAL_FAILURE_CODE
#endif

#define ASSERT_PRINTF(_cond_, _retcode_, _fmt_, ...)  do {  \
	if (UNLIKELY( ! (_cond_) ))                             \
	{                                                       \
		ASSERT_PRINTF_CALL(_fmt_, ##__VA_ARGS__);           \
		ASSERT_ADDITIONAL_FAILURE_CODE                      \
		ASSERT_RETCODE_VARIABLE_NAME = (_retcode_);         \
		goto ASSERT_GOTO_LABEL;                             \
	}                                                       \
} while(0)
#define ASSERT_STRERROR(_cond_, _errno_, _retcode_, _msg_)         \
	ASSERT_PRINTF(_cond_, _retcode_, "%s: %s", (_msg_), strerror((_errno_)))
#define ASSERT_PERROR(_cond_, _retcode_, _msg_)       \
	ASSERT_STRERROR(_cond_, errno, _retcode_, _msg_)
#define ASSERT_SILENT(_cond_, _retcode_)  do {         \
	if (UNLIKELY( ! (_cond_) ))                        \
	{                                                  \
		ASSERT_ADDITIONAL_FAILURE_CODE                 \
		ASSERT_RETCODE_VARIABLE_NAME = (_retcode_);    \
		goto ASSERT_GOTO_LABEL;                        \
	}                                                  \
} while(0)


#endif  // VFS_PROPRIETARY_ASSERT_H_
