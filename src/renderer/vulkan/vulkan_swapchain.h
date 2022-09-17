/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan.h"

#include <pch.h>

i32 vulkanCreateSwapchain(void);
i32 vulkanDestroySwapchain(void);

#endif
