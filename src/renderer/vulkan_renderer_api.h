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

typedef enum {
	VULKAN_RENDERER_API_OK,
	VULKAN_RENDERER_API_REQUIRED_VULKAN_VERSION_IS_NOT_SUPPORTED,
	VULKAN_RENDERER_API_COULD_NOT_CREATE_INSTANCE,
	VULKAN_RENDERER_API_COULD_NOT_PICK_PHYSICAL_DEVICE,
	VULKAN_RENDERER_API_NO_PHYSICAL_DEVICE_GROUPS,
	VULKAN_RENDERER_API_NO_QUEUE_FAMILY_PROPERTIES,
	VULKAN_RENDERER_API_NO_QUEUE_WITH_GRAPHICS_BIT,
	VULKAN_RENDERER_API_COULD_NOT_CREATE_DEVICE,
} VulkanRendererApiError;

VulkanRendererApiError vulkanRendererApiCreate(VulkanRendererApi* self, Window* window);
VulkanRendererApiError vulkanRendererApiDestroy(VulkanRendererApi* self);

#endif
