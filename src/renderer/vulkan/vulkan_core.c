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

static i32 sCreateInstance(void)
{
	VkApplicationInfo applicationInfo = {
		.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.apiVersion         = VK_API_VERSION_1_1,
		.applicationVersion = VK_MAKE_VERSION(0, 1, 0), /* TODO: */
		.engineVersion      = VK_MAKE_VERSION(0, 1, 0), /* TODO: */
		.pApplicationName   = "",                       /* TODO: */
		.pEngineName        = "pogona",
	};
	VkInstanceCreateInfo instanceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &applicationInfo,
	};

	PVK_VERIFY(vkCreateInstance(&instanceCreateInfo, NULL, &gVulkanCore.instance));
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
	vkDestroyInstance(gVulkanCore.instance, NULL);
	return 0;
}

#endif
