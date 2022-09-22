/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan.h"

i32 vulkanCreateSemaphore(VkSemaphore* semaphore);
i32 vulkanCreateFence(VkFence* fence, bool signaled);

VkImageMemoryBarrier2 vulkanCreateImageBarrier(VkImage image, VkPipelineStageFlags2 srcStageMask,
		VkAccessFlags2 srcAccessMask, VkImageLayout oldLayout, VkPipelineStageFlags2 dstStageMask,
		VkAccessFlags2 dstAccessMask, VkImageLayout newLayout, VkImageAspectFlags aspectMask, u32 baseMipLevel,
		u32 levelCount);
VkBufferMemoryBarrier2 vulkanCreateBufferBarrier(VkBuffer buffer, VkPipelineStageFlagBits2 srcStageMask,
		VkAccessFlags2 srcAccessMask, VkPipelineStageFlags2 dstStageMask, VkAccessFlags2 dstAccessMask);
void vulkanCreatePipelineBarrier(VkDependencyFlags dependencyFlags, u32 bufferBarriersCount,
		const VkBufferMemoryBarrier2* bufferBarriers, u32 imageBarriersCount, const VkImageMemoryBarrier2* imageBarriers);

#endif
