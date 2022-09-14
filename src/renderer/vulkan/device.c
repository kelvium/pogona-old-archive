/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "device.h"

#include <pogona/logger.h>

i32 vulkanCreateDevice(VulkanRendererApi* self)
{
	i32 error;

	u32 pickedQueueFamilyPropertiesIndex;
	error = vulkanPickQueueFamilyPropertiesIndex(self, &pickedQueueFamilyPropertiesIndex);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not pick queue family properties: %d\n", error);
		return error;
	}

	float queuePriorities[] = { 1.0 };
	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCount = 1,
		.queueFamilyIndex = pickedQueueFamilyPropertiesIndex,
		.pQueuePriorities = queuePriorities,
	};

	VkDeviceCreateInfo deviceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pQueueCreateInfos = &deviceQueueCreateInfo,
		.queueCreateInfoCount = 1,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = NULL,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = NULL,
		.pEnabledFeatures = NULL,
	};

	VkResult result;
	result = vkCreateDevice(self->vulkanGlobals->physicalDevice, &deviceCreateInfo, NULL, &self->vulkanGlobals->device);
	if (result != VK_SUCCESS) {
		LOGGER_ERROR("could not create device: %d\n", result);
		return VULKAN_RENDERER_API_COULD_NOT_CREATE_DEVICE;
	}
	LOGGER_DEBUG("created a device\n");
	return VULKAN_RENDERER_API_OK;
}

#endif
