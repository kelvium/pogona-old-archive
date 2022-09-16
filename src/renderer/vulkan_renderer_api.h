/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan/vulkan.h"

#include <pogona/window.h>

typedef struct {
	Window* window;
	VulkanGlobals* vulkanGlobals;
} VulkanRendererApi;

i32 vulkanRendererApiCreate(VulkanRendererApi* self, Window* window);
i32 vulkanRendererApiDestroy(VulkanRendererApi* self);

#endif
