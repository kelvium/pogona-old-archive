/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pogona/logger.h>
#include <pogona/types.h>
#include <volk.h>

#define PVK_VERIFY(x)                               \
	do {                                              \
		i32 error = x;                                  \
		if (error < 0) {                                \
			LOGGER_ERROR("`%s` failed: %i\n", #x, error); \
			return 1;                                     \
		}                                               \
	} while (false)

#endif
