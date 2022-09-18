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
	VkQueue queue;
	VkCommandPool commandPool;
	VkCommandBuffer commandBuffer;
	struct {
		VkSurfaceKHR surface;

		u32 surfaceFormatsCount;
		VkSurfaceFormatKHR* surfaceFormats;
		u32 presentModesCount;
		VkPresentModeKHR* presentModes;
	} surface;
	VkRenderPass renderPass;
} VulkanCore;

extern VulkanCore gVulkanCore;

i32 vulkanInit(Window* window);
i32 vulkanFini(void);

#endif
