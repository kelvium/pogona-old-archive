/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan.h"

typedef struct {
	VkPhysicalDevice physicalDevice;
	u32 queueFamilyIndex;
} PhysicalDevice;

typedef struct {
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugUtilsMessenger;
	PhysicalDevice physicalDevice;
	VkDevice device;
} VulkanCore;

extern VulkanCore gVulkanCore;

i32 vulkanInit(void);
i32 vulkanFini(void);

#endif
