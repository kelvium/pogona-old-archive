/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan.h"

#include <pogona/window.h>

typedef struct {
	VkPhysicalDevice physicalDevice;
	u32 queueFamilyIndex;
} PhysicalDevice;

typedef struct {
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugUtilsMessenger;
	PhysicalDevice physicalDevice;
	VkDevice device;
	VkCommandPool commandPool;
	VkCommandBuffer commandBuffer;
	VkSurfaceKHR surface;
} VulkanCore;

extern VulkanCore gVulkanCore;

i32 vulkanInit(Window* window);
i32 vulkanFini(void);

#endif
