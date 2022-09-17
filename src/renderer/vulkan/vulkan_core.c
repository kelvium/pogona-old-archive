/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan_core.h"
#include "vulkan_surface.h"

#include <pch.h>
#include <pogona/vector.h>

VulkanCore gVulkanCore = { 0 };

static VkBool32 VKAPI_PTR sDebugCallback(VkDebugUtilsMessageSeverityFlagsEXT severity,
		VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* data)
{
	(void) severity;
	(void) type;
	(void) data;

	switch (callbackData->messageIdNumber) {
	// Until https://github.com/KhronosGroup/Vulkan-ValidationLayers/issues/4526 is fixed:
	case 0x3e33626b:
	case 0x3a56b425:
	case 0x92b01222:
	case 0x3b896d80:
	case 0x36944ae0:
	case 0x1c7693fb:
		return VK_FALSE;
	}

	LOGGER_DEBUG("validation: %s\n", callbackData->pMessage);
	return VK_FALSE;
}

static i32 sCreateInstance(void)
{
	u32 supportedVersion = 0;
	vkEnumerateInstanceVersion(&supportedVersion);
	if (supportedVersion < VK_API_VERSION_1_1) {
		LOGGER_ERROR("vulkan 1.1 is not supported\n");
		return -1;
	}

	StringVector extensions;
	StringVector layers;
	VECTOR_INIT(&extensions);
	VECTOR_INIT(&layers);

	/* this variable is required because our vector implementation takes a pointer :-p */
	const char* dataToPush = VK_KHR_SURFACE_EXTENSION_NAME;
	VECTOR_PUSH(&extensions, &dataToPush);
#ifdef POGONA_WAYLAND_SUPPORT
	dataToPush = VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME;
	VECTOR_PUSH(&extensions, &dataToPush);
#endif

#ifndef NDEBUG
	dataToPush = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
	VECTOR_PUSH(&extensions, &dataToPush);
	dataToPush = "VK_LAYER_KHRONOS_validation";
	VECTOR_PUSH(&layers, &dataToPush);
#endif

	VkApplicationInfo applicationInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.apiVersion = VK_API_VERSION_1_1,
		.applicationVersion = VK_MAKE_VERSION(0, 1, 0), /* TODO: */
		.engineVersion = VK_MAKE_VERSION(0, 1, 0),      /* TODO: */
		.pApplicationName = "",                         /* TODO: */
		.pEngineName = "pogona",
	};
	VkInstanceCreateInfo instanceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &applicationInfo,
		.enabledLayerCount = layers.size,
		.enabledExtensionCount = extensions.size,
		.ppEnabledLayerNames = layers.data,
		.ppEnabledExtensionNames = extensions.data,
	};

#ifndef NDEBUG
	VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.pfnUserCallback = sDebugCallback,
		.pUserData = NULL,
		.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
		.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
	};
	instanceCreateInfo.pNext = &debugUtilsMessengerCreateInfo;
#endif

	PVK_VERIFY(vkCreateInstance(&instanceCreateInfo, NULL, &gVulkanCore.instance));
	volkLoadInstance(gVulkanCore.instance);

#ifndef NDEBUG
	PVK_VERIFY(vkCreateDebugUtilsMessengerEXT(
			gVulkanCore.instance, &debugUtilsMessengerCreateInfo, NULL, &gVulkanCore.debugUtilsMessenger));
#endif

	VECTOR_FREE(&extensions);
	VECTOR_FREE(&layers);
	return 0;
}

static i32 sEnumeratePhysicalDevices(void)
{
	{
		u32 physicalDeviceGroupCount = 0;
		VkPhysicalDeviceGroupProperties* physicalDeviceGroupPropertieses = NULL; /* such a good name lol */

		PVK_VERIFY(vkEnumeratePhysicalDeviceGroups(gVulkanCore.instance, &physicalDeviceGroupCount, NULL));
		physicalDeviceGroupPropertieses = calloc(physicalDeviceGroupCount, sizeof(VkPhysicalDeviceGroupProperties));
		PVK_VERIFY(vkEnumeratePhysicalDeviceGroups(
				gVulkanCore.instance, &physicalDeviceGroupCount, physicalDeviceGroupPropertieses));

		// TODO: implement fallback device picking
		VkPhysicalDevice pickedPhysicalDevice = NULL;
		for (u32 i = 0; i < physicalDeviceGroupCount; ++i) {
			VkPhysicalDeviceGroupProperties physicalDeviceGroupProperties = physicalDeviceGroupPropertieses[i];
			for (u32 j = 0; j < physicalDeviceGroupProperties.physicalDeviceCount; ++j) {
				VkPhysicalDevice physicalDevice = physicalDeviceGroupProperties.physicalDevices[j];

				VkPhysicalDeviceProperties physicalDeviceProperties;
				vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

				// TODO: check if physicalDevice supports Vulkan 1.1

				if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
					LOGGER_INFO("picked a physical device: `%s`\n", physicalDeviceProperties.deviceName);
					pickedPhysicalDevice = physicalDevice;
					break;
				}
			}
		}
		free(physicalDeviceGroupPropertieses);

		if (!pickedPhysicalDevice) {
			LOGGER_ERROR("could not pick a physical device\n");
			return -1;
		}
		gVulkanCore.physicalDevice.physicalDevice = pickedPhysicalDevice;
	}

	{
		u32 queueFamilyPropertiesCount = 0;
		VkQueueFamilyProperties* queueFamilyPropertieses = NULL;

		vkGetPhysicalDeviceQueueFamilyProperties(
				gVulkanCore.physicalDevice.physicalDevice, &queueFamilyPropertiesCount, NULL);
		queueFamilyPropertieses = calloc(queueFamilyPropertiesCount, sizeof(VkQueueFamilyProperties));
		vkGetPhysicalDeviceQueueFamilyProperties(
				gVulkanCore.physicalDevice.physicalDevice, &queueFamilyPropertiesCount, queueFamilyPropertieses);

		gVulkanCore.physicalDevice.queueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		for (u32 i = 0; i < queueFamilyPropertiesCount; ++i) {
			VkQueueFamilyProperties queueFamilyProperties = queueFamilyPropertieses[i];
			if (queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				gVulkanCore.physicalDevice.queueFamilyIndex = i;
				break;
			}
		}
		free(queueFamilyPropertieses);

		if (gVulkanCore.physicalDevice.queueFamilyIndex == VK_QUEUE_FAMILY_IGNORED) {
			LOGGER_ERROR("could not pick a queue family with graphics bit set\n");
			return -1;
		}
	}
	return 0;
}

static i32 sCreateDevice(void)
{
	/* we don't need a debug extension or something, so we can use a simple array */
	const char* extensions[] = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	const float queuePriorities[] = { 1.f };
	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.pQueuePriorities = queuePriorities,
		.queueCount = 1,
		.queueFamilyIndex = gVulkanCore.physicalDevice.queueFamilyIndex,
	};

	VkDeviceCreateInfo deviceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &deviceQueueCreateInfo,
		.enabledLayerCount = 0,
		.enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0]),
		.ppEnabledLayerNames = NULL,
		.ppEnabledExtensionNames = extensions,
		.pEnabledFeatures = NULL,
	};

	PVK_VERIFY(vkCreateDevice(gVulkanCore.physicalDevice.physicalDevice, &deviceCreateInfo, NULL, &gVulkanCore.device));
	volkLoadDevice(gVulkanCore.device);
	return 0;
}

static i32 sCreateCommandPool(void)
{
	VkCommandPoolCreateInfo commandPoolCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.queueFamilyIndex = gVulkanCore.physicalDevice.queueFamilyIndex,
		.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
	};
	PVK_VERIFY(vkCreateCommandPool(gVulkanCore.device, &commandPoolCreateInfo, NULL, &gVulkanCore.commandPool));

	VkCommandBuffer commandBuffers[1] = { 0 };
	VkCommandBufferAllocateInfo commandBufferAllocateInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.commandBufferCount = 1,
		.commandPool = gVulkanCore.commandPool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	};
	PVK_VERIFY(vkAllocateCommandBuffers(gVulkanCore.device, &commandBufferAllocateInfo, commandBuffers));

	gVulkanCore.commandBuffer = commandBuffers[0];
	return 0;
}

i32 vulkanInit(Window* window)
{
	if (sCreateInstance() < 0) {
		LOGGER_ERROR("could not create an instance\n");
		return -1;
	}

	if (sEnumeratePhysicalDevices() < 0) {
		LOGGER_ERROR("could not enumerate physical devices\n");
		return -1;
	}

	if (sCreateDevice() < 0) {
		LOGGER_ERROR("could not create a device\n");
		return -1;
	}

	if (sCreateCommandPool() < 0) {
		LOGGER_ERROR("could not create a command pool\n");
		return -1;
	}

	if (vulkanCreateSurface(window, &gVulkanCore.surface.surface) < 0) {
		LOGGER_ERROR("could not create a surface\n");
		return -1;
	}
	return 0;
}

i32 vulkanFini()
{
	vulkanDestroySurface();
	vkDestroyCommandPool(gVulkanCore.device, gVulkanCore.commandPool, NULL);
	vkDestroyDevice(gVulkanCore.device, NULL);
	vkDestroyDebugUtilsMessengerEXT(gVulkanCore.instance, gVulkanCore.debugUtilsMessenger, NULL);
	vkDestroyInstance(gVulkanCore.instance, NULL);
	return 0;
}

#endif
