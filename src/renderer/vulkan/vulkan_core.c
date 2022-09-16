/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan_core.h"

#include <pch.h>

VulkanCore gVulkanCore = { 0 };

static VkBool32 VKAPI_PTR sDebugCallback(VkDebugUtilsMessageSeverityFlagsEXT severity,
		VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* data)
{
	(void) severity;
	(void) type;
	(void) data;

	LOGGER_DEBUG("validation: %s\n", callbackData->pMessage);
	return VK_FALSE;
}

static i32 sCreateInstance(void)
{
	// FIXME: remove these hacks
#ifndef NDEBUG
	const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
	const u32 layersCount = 1;

	const char* extensions[] = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
	const u32 extensionsCount = 1;
#else
	const char* layers[] = {};
	const u32 layersCount = 0;

	const char* extensions[] = {};
	const u32 extensionsCount = 0;
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
		.enabledLayerCount = layersCount,
		.enabledExtensionCount = extensionsCount,
		.ppEnabledLayerNames = layers,
		.ppEnabledExtensionNames = extensions,
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
	return 0;
}

i32 vulkanInit()
{
	if (sCreateInstance() < 0) {
		LOGGER_ERROR("could not create an instance\n");
		return -1;
	}
	return 0;
}

i32 vulkanFini()
{
	vkDestroyDebugUtilsMessengerEXT(gVulkanCore.instance, gVulkanCore.debugUtilsMessenger, NULL);
	vkDestroyInstance(gVulkanCore.instance, NULL);
	return 0;
}

#endif
