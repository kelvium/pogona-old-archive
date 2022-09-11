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

VulkanRendererApiError vulkanRendererApiCreate(VulkanRendererApi* self, Window* window)
{
	self->window = window;
	self->vulkanGlobals = calloc(1, sizeof(VulkanGlobals));

	volkInitialize();

	VulkanRendererApiError error;
	error = vulkanCreateInstance(self);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not create an instance: %d\n", error);
		return error;
	}
	volkLoadInstance(self->vulkanGlobals->instance);

	error = vulkanPickPhysicalDevice(self);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not pick a physical device: %d\n", error);
		return error;
	}

	error = vulkanCreateDevice(self);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not create a device: %d\n", error);
		return error;
	}
	volkLoadDevice(self->vulkanGlobals->device);
	return VULKAN_RENDERER_API_OK;
}

VulkanRendererApiError vulkanRendererApiDestroy(VulkanRendererApi* self)
{
	vkDestroyDevice(self->vulkanGlobals->device, NULL);
	LOGGER_DEBUG("destroyed the device\n");

	vkDestroyInstance(self->vulkanGlobals->instance, NULL);
	LOGGER_DEBUG("destroyed the instance\n");

	free(self->vulkanGlobals);
	return VULKAN_RENDERER_API_OK;
}

#endif
