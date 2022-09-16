/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan/device.h"
#include "vulkan/instance.h"
#include "vulkan/physical_device.h"
#include "vulkan_renderer_api.h"

#include <pch.h>
#include <pogona/logger.h>

i32 vulkanRendererApiCreate(VulkanRendererApi* self, Window* window)
{
	self->window = window;
	self->vulkanGlobals = calloc(1, sizeof(VulkanGlobals));

	volkInitialize();

	i32 error;
	error = vulkanCreateInstance(self);
	if (error < 0) {
		LOGGER_ERROR("could not create an instance\n");
		return error;
	}
	volkLoadInstance(self->vulkanGlobals->instance);

	error = vulkanPickPhysicalDevice(self);
	if (error < 0) {
		LOGGER_ERROR("could not pick a physical device\n");
		return error;
	}

	error = vulkanCreateDevice(self);
	if (error < 0) {
		LOGGER_ERROR("could not create a device\n");
		return error;
	}
	volkLoadDevice(self->vulkanGlobals->device);
	return 0;
}

i32 vulkanRendererApiDestroy(VulkanRendererApi* self)
{
	vkDestroyDevice(self->vulkanGlobals->device, NULL);
	vkDestroyInstance(self->vulkanGlobals->instance, NULL);
	free(self->vulkanGlobals);
	return 0;
}

#endif
