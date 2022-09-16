/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan_renderer_api.h"

#include <pch.h>
#include <pogona/logger.h>

i32 vulkanRendererApiCreate(VulkanRendererApi* self, Window* window)
{
	self->window = window;

	volkInitialize();
	return 0;
}

i32 vulkanRendererApiDestroy(VulkanRendererApi* self)
{
	(void) self;
	return 0;
}

#endif
