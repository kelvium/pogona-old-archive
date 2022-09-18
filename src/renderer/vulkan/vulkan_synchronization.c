/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan_core.h"
#include "vulkan_synchronization.h"

#include <pch.h>

i32 vulkanCreateSemaphore(VkSemaphore* semaphore)
{
	VkSemaphoreCreateInfo semaphoreCreateInfo = { .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
	PVK_VERIFY(vkCreateSemaphore(gVulkanCore.device, &semaphoreCreateInfo, NULL, semaphore));
	return 0;
}

i32 vulkanCreateFence(VkFence* fence, bool signaled)
{
	VkFenceCreateInfo fenceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.flags = signaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0,
	};
	PVK_VERIFY(vkCreateFence(gVulkanCore.device, &fenceCreateInfo, NULL, fence));
	return 0;
}

VkImageMemoryBarrier2 vulkanCreateImageBarrier(VkImage image, VkPipelineStageFlags2 srcStageMask,
		VkAccessFlags2 srcAccessMask, VkImageLayout oldLayout, VkPipelineStageFlags2 dstStageMask,
		VkAccessFlags2 dstAccessMask, VkImageLayout newLayout, VkImageAspectFlags aspectMask, u32 baseMipLevel,
		u32 levelCount)
{
	VkImageMemoryBarrier2 imageBarrier = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
		.srcStageMask = srcStageMask,
		.srcAccessMask = srcAccessMask,
		.dstStageMask = dstStageMask,
		.dstAccessMask = dstAccessMask,
		.oldLayout = oldLayout,
		.newLayout = newLayout,
		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.image = image,
		.subresourceRange = {
			.aspectMask = aspectMask,
			.baseMipLevel = baseMipLevel,
			.levelCount = levelCount,
			.layerCount = VK_REMAINING_ARRAY_LAYERS,
		},
	};
	return imageBarrier;
}

VkBufferMemoryBarrier2 vulkanCreateBufferBarrier(VkBuffer buffer, VkPipelineStageFlagBits2 srcStageMask,
		VkAccessFlags2 srcAccessMask, VkPipelineStageFlags2 dstStageMask, VkAccessFlags2 dstAccessMask)
{
	VkBufferMemoryBarrier2 bufferBarrier = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2,
		.srcStageMask = srcStageMask,
		.srcAccessMask = srcAccessMask,
		.dstStageMask = dstStageMask,
		.dstAccessMask = dstAccessMask,
		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.buffer = buffer,
		.offset = 0,
		.size = VK_WHOLE_SIZE,
	};
	return bufferBarrier;
}

void vulkanCreatePipelineBarrier(VkDependencyFlags dependencyFlags, u32 bufferBarriersCount,
		const VkBufferMemoryBarrier2* bufferBarriers, u32 imageBarriersCount, const VkImageMemoryBarrier2* imageBarriers)
{
	VkDependencyInfo dependencyInfo = {
		.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
		.dependencyFlags = dependencyFlags,
		.bufferMemoryBarrierCount = bufferBarriersCount,
		.imageMemoryBarrierCount = imageBarriersCount,
		.pBufferMemoryBarriers = bufferBarriers,
		.pImageMemoryBarriers = imageBarriers,
	};
	vkCmdPipelineBarrier2(gVulkanCore.commandBuffer, &dependencyInfo);
}

#endif
