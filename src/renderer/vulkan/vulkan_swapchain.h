/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan.h"

#include <pch.h>

typedef struct {
	u32 width, height;

	VkSwapchainKHR swapchain;
	VkFormat imageFormat;
	VkColorSpaceKHR colorSpace;

	u32 imagesCount;
	VkImage* images;
	VkImageView* imageViews;
	VkFramebuffer* framebuffers;
} Swapchain;

extern Swapchain gSwapchain;

i32 vulkanCreateSwapchain(void);
i32 vulkanAcquireNextImage(u32* imageIndex, VkSemaphore semaphore);
i32 vulkanDestroySwapchain(void);

i32 vulkanSwapchainInitImageViews(void);
i32 vulkanSwapchainInitFramebuffers(void);

#endif
