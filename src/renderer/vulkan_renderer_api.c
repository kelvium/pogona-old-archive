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

const char* vulkanRendererApiErrorToString(i32 error)
{
	switch (error) {
	case VULKAN_RENDERER_API_OK:
		return "Ok";
	case VULKAN_RENDERER_API_REQUIRED_VULKAN_VERSION_IS_NOT_SUPPORTED:
		return "Required Vulkan version is not supported";
	case VULKAN_RENDERER_API_COULD_NOT_CREATE_INSTANCE:
		return "Could not create instance";
	case VULKAN_RENDERER_API_COULD_NOT_PICK_PHYSICAL_DEVICE:
		return "Could not pick physical device";
	case VULKAN_RENDERER_API_NO_PHYSICAL_DEVICE_GROUPS:
		return "No physical device groups";
	case VULKAN_RENDERER_API_NO_QUEUE_FAMILY_PROPERTIES:
		return "No queue family properties";
	case VULKAN_RENDERER_API_NO_QUEUE_WITH_GRAPHICS_BIT:
		return "No queue with graphics bit";
	case VULKAN_RENDERER_API_COULD_NOT_CREATE_DEVICE:
		return "Could not create device";
	default:
		return "(invalid)";
	}
}

i32 vulkanRendererApiCreate(VulkanRendererApi* self, Window* window)
{
	self->window = window;
	self->vulkanGlobals = calloc(1, sizeof(VulkanGlobals));

	volkInitialize();

	i32 error;
	error = vulkanCreateInstance(self);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not create an instance: %s\n", vulkanRendererApiErrorToString(error));
		return error;
	}
	volkLoadInstance(self->vulkanGlobals->instance);

	error = vulkanPickPhysicalDevice(self);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not pick a physical device: %s\n", vulkanRendererApiErrorToString(error));
		return error;
	}

	error = vulkanCreateDevice(self);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not create a device: %s\n", vulkanRendererApiErrorToString(error));
		return error;
	}
	volkLoadDevice(self->vulkanGlobals->device);
	return VULKAN_RENDERER_API_OK;
}

i32 vulkanRendererApiDestroy(VulkanRendererApi* self)
{
	vkDestroyDevice(self->vulkanGlobals->device, NULL);
	LOGGER_DEBUG("destroyed the device\n");

	vkDestroyInstance(self->vulkanGlobals->instance, NULL);
	LOGGER_DEBUG("destroyed the instance\n");

	free(self->vulkanGlobals);
	return VULKAN_RENDERER_API_OK;
}

#endif
