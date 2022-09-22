/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan/vulkan_core.h"
#include "vulkan/vulkan_render.h"
#include "vulkan/vulkan_swapchain.h"
#include "vulkan/vulkan_synchronization.h"
#include "vulkan_renderer_api.h"

#include <pch.h>
#include <pogona/logger.h>

VulkanRender gVulkanRender = { 0 };

static VkSemaphore sImageAvailableSemaphore = NULL;
static VkSemaphore sRenderFinishedSemaphore = NULL;
static VkFence sInFlightFence = NULL;

i32 vulkanRendererApiCreate(Window* window)
{
	gVulkanRender.window = window;

	volkInitialize();
	if (vulkanInit(window) < 0) {
		LOGGER_ERROR("failed to initialize vulkan\n");
		return -1;
	}

	assert(vulkanCreateSemaphore(&sImageAvailableSemaphore) >= 0);
	assert(vulkanCreateSemaphore(&sRenderFinishedSemaphore) >= 0);
	assert(vulkanCreateFence(&sInFlightFence, true) >= 0);
	return 0;
}

i32 vulkanRendererApiDraw(void)
{
	PVK_VERIFY(vkWaitForFences(gVulkanCore.device, 1, &sInFlightFence, VK_TRUE, UINT64_MAX));
	PVK_VERIFY(vkResetFences(gVulkanCore.device, 1, &sInFlightFence));

	VkImage image;
	u32 imageIndex;
	PVK_VERIFY(vulkanAcquireNextImage(&image, &imageIndex, sImageAvailableSemaphore) >= 0);

	vkResetCommandBuffer(gVulkanCore.commandBuffer, 0);

	VkCommandBufferBeginInfo commandBufferBeginInfo = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	PVK_VERIFY(vkBeginCommandBuffer(gVulkanCore.commandBuffer, &commandBufferBeginInfo));

	VkClearValue clearValue = { { { 0.f, 0.f, 0.f, 1.f } } };
	VkRenderPassBeginInfo  renderPassBeginInfo = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.renderPass = gVulkanCore.renderPass,
		.framebuffer = gSwapchain.framebuffers[imageIndex],
		.renderArea = {
			.offset = { 0, 0 },
			.extent = { gSwapchain.width, gSwapchain.height },
		},
		.clearValueCount = 1,
		.pClearValues = &clearValue,
	};
	vkCmdBeginRenderPass(gVulkanCore.commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(gVulkanCore.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, gVulkanCore.pipeline.pipeline);
	VkViewport viewport = {
		.x = 0.f,
		.y = 0.f,
		.width = (f32) gSwapchain.width,
		.height = (f32) gSwapchain.height,
		.minDepth = 0.f,
		.maxDepth = 1.f,
	};
	vkCmdSetViewport(gVulkanCore.commandBuffer, 0, 1, &viewport);

	VkRect2D scissor = {
		.offset = { 0, 0 },
		.extent = { .width = gSwapchain.width, .height = gSwapchain.height },
	};
	vkCmdSetScissor(gVulkanCore.commandBuffer, 0, 1, &scissor);

	vkCmdDraw(gVulkanCore.commandBuffer, 3, 1, 0, 0);

	vkCmdEndRenderPass(gVulkanCore.commandBuffer);
	PVK_VERIFY(vkEndCommandBuffer(gVulkanCore.commandBuffer));

	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	VkSubmitInfo submitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &sImageAvailableSemaphore,
		.pWaitDstStageMask = waitStages,
		.commandBufferCount = 1,
		.pCommandBuffers = &gVulkanCore.commandBuffer,
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &sRenderFinishedSemaphore,
	};
	PVK_VERIFY(vkQueueSubmit(gVulkanCore.queue, 1, &submitInfo, sInFlightFence));

	VkPresentInfoKHR presentInfo = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.swapchainCount = 1,
		.pSwapchains = &gSwapchain.swapchain,
		.pImageIndices = &imageIndex,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &sRenderFinishedSemaphore,
	};
	PVK_VERIFY(vkQueuePresentKHR(gVulkanCore.queue, &presentInfo));
	return 0;
}

i32 vulkanRendererApiDestroy(void)
{
	vkDestroyFence(gVulkanCore.device, sInFlightFence, NULL);
	vkDestroySemaphore(gVulkanCore.device, sRenderFinishedSemaphore, NULL);
	vkDestroySemaphore(gVulkanCore.device, sImageAvailableSemaphore, NULL);

	if (vulkanFini() < 0) {
		LOGGER_ERROR("failed to finalize vulkan\n");
		return -1;
	}
	return 0;
}

#endif
