/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "physical_device.h"

#include <pch.h>
#include <pogona/logger.h>

VulkanRendererApiError vulkanPickPhysicalDevice(VulkanRendererApi* self)
{
	VkResult result;

	// get physical device group count
	u32 physicalDeviceGroupsCount = 0;
	result = vkEnumeratePhysicalDeviceGroups(self->vulkanGlobals->instance, &physicalDeviceGroupsCount, NULL);
	if (result != VK_SUCCESS) {
		LOGGER_ERROR("could not enumerate physical device groups: %d\n", result);
		return VULKAN_RENDERER_API_COULD_NOT_PICK_PHYSICAL_DEVICE;
	}

	if (physicalDeviceGroupsCount == 0) {
		LOGGER_ERROR("no physical devices groups\n");
		return VULKAN_RENDERER_API_NO_PHYSICAL_DEVICE_GROUPS;
	}

	// get physical device group properties
	VkPhysicalDeviceGroupProperties* physicalDeviceGroupsProperties
			= calloc(physicalDeviceGroupsCount, sizeof(VkPhysicalDeviceGroupProperties));
	result = vkEnumeratePhysicalDeviceGroups(
			self->vulkanGlobals->instance, &physicalDeviceGroupsCount, physicalDeviceGroupsProperties);
	if (result != VK_SUCCESS) {
		LOGGER_ERROR("could not enumerate physical device groups: %d\n", result);
		return VULKAN_RENDERER_API_COULD_NOT_PICK_PHYSICAL_DEVICE;
	}

	VkPhysicalDevice fallbackPhysicalDevice = NULL;
	for (u32 i = 0; i < physicalDeviceGroupsCount; i++) {
		VkPhysicalDeviceGroupProperties physicalDeviceGroupProperties = physicalDeviceGroupsProperties[i];

		LOGGER_DEBUG("physical device group properties %d:\n", i);
		LOGGER_DEBUG(" physical devices count: %d\n", physicalDeviceGroupProperties.physicalDeviceCount);
		for (u32 j = 0; j < physicalDeviceGroupProperties.physicalDeviceCount; j++) {
			VkPhysicalDevice physicalDevice = physicalDeviceGroupProperties.physicalDevices[j];

			VkPhysicalDeviceProperties physicalDeviceProperties;
			vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

			LOGGER_DEBUG(" physical device %d:\n", j);
			LOGGER_DEBUG("   deviceName: %s\n", physicalDeviceProperties.deviceName);
			LOGGER_DEBUG("   api version: %d.%d.%d\n", VK_API_VERSION_MAJOR(physicalDeviceProperties.apiVersion),
					VK_API_VERSION_MINOR(physicalDeviceProperties.apiVersion),
					VK_VERSION_PATCH(physicalDeviceProperties.apiVersion));

			if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
				self->vulkanGlobals->physicalDevice = physicalDevice;
				LOGGER_INFO("picked a discrete gpu: %s\n", physicalDeviceProperties.deviceName);
			} else if (!fallbackPhysicalDevice) {
				fallbackPhysicalDevice = physicalDevice;
				LOGGER_INFO("picked %s as the fallback physical device\n", physicalDeviceProperties.deviceName);
			}
		}
	}

	if (!self->vulkanGlobals->physicalDevice && fallbackPhysicalDevice) {
		self->vulkanGlobals->physicalDevice = fallbackPhysicalDevice;
		LOGGER_INFO("picked the fallback physical device\n");
	}

	free(physicalDeviceGroupsProperties);
	return VULKAN_RENDERER_API_OK;
}

VulkanRendererApiError vulkanPickQueueFamilyPropertiesIndex(
		VulkanRendererApi* self, u32* pickedQueueFamilyPropertiesIndex)
{
	// get queue family property count
	u32 queueFamilyPropertyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(self->vulkanGlobals->physicalDevice, &queueFamilyPropertyCount, NULL);

	if (queueFamilyPropertyCount == 0) {
		LOGGER_ERROR("no queue family properties\n");
		return VULKAN_RENDERER_API_NO_QUEUE_FAMILY_PROPERTIES;
	}

	// get queue family properties
	VkQueueFamilyProperties* queueFamilyPropertiesArray
			= calloc(queueFamilyPropertyCount, sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(
			self->vulkanGlobals->physicalDevice, &queueFamilyPropertyCount, queueFamilyPropertiesArray);

	bool picked = false;
	for (u32 i = 0; i < queueFamilyPropertyCount; i++) {
		VkQueueFamilyProperties queueFamilyProperties = queueFamilyPropertiesArray[i];

		bool supportsGraphics = queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT;

		LOGGER_DEBUG("queue family properties %d:\n", i);
		LOGGER_DEBUG(" queue count: %d\n", queueFamilyProperties.queueCount);
		LOGGER_DEBUG(" supports graphics: %s\n", supportsGraphics ? "true" : "false");

		if (supportsGraphics) {
			*pickedQueueFamilyPropertiesIndex = i;
			picked = true;
		}
	}

	free(queueFamilyPropertiesArray);
	if (!picked)
		return VULKAN_RENDERER_API_NO_QUEUE_WITH_GRAPHICS_BIT;
	LOGGER_DEBUG("picked queue family properties index %d\n", *pickedQueueFamilyPropertiesIndex);
	return VULKAN_RENDERER_API_OK;
}

#endif
