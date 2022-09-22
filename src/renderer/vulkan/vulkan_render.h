/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan.h"

#include <pogona/window.h>

/* All fields of this struct should be initialized by the renderer api */
typedef struct {
	Window* window;
} VulkanRender;

extern VulkanRender gVulkanRender;

#endif
