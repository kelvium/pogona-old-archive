/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#ifdef POGONA_WAYLAND_SUPPORT
#define VK_USE_PLATFORM_WAYLAND_KHR
#endif
#include <volk.h>

#endif
