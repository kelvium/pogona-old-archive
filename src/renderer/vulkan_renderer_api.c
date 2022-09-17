/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan_renderer_api.h"
#include "vulkan/vulkan_core.h"

#include <pch.h>
#include <pogona/logger.h>

i32 vulkanRendererApiCreate(VulkanRendererApi* self, Window* window)
{
	self->window = window;

	volkInitialize();
	if (vulkanInit(window) < 0) {
		LOGGER_ERROR("failed to initialize vulkan\n");
		return -1;
	}
	return 0;
}

i32 vulkanRendererApiDestroy(VulkanRendererApi* self)
{
	(void) self;

	if (vulkanFini() < 0) {
		LOGGER_ERROR("failed to finalize vulkan\n");
		return -1;
	}
	return 0;
}

#endif
