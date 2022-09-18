/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan_core.h"
#include "vulkan_render_pass.h"
#include "vulkan_swapchain.h"

#include <pch.h>

i32 vulkanCreateRenderPass(VkRenderPass* renderPass)
{
	VkAttachmentDescription attachmentDescriptions[1] = { 0 };
	attachmentDescriptions[0].format = gSwapchain.imageFormat;
	attachmentDescriptions[0].samples = VK_SAMPLE_COUNT_1_BIT;
	attachmentDescriptions[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachmentDescriptions[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachmentDescriptions[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachmentDescriptions[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachmentDescriptions[0].initialLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL;
	attachmentDescriptions[0].finalLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL;

	VkAttachmentReference colorAttachments[1] = { { 0, VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL } };
	VkSubpassDescription subpassDescriptions[1] = {
		{
				.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
				.colorAttachmentCount = sizeof(colorAttachments) / sizeof(colorAttachments[0]),
				.pColorAttachments = colorAttachments,
		},
	};

	VkRenderPassCreateInfo renderPassCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.attachmentCount = sizeof(attachmentDescriptions) / sizeof(attachmentDescriptions[0]),
		.pAttachments = attachmentDescriptions,
		.subpassCount = sizeof(subpassDescriptions) / sizeof(subpassDescriptions[0]),
		.pSubpasses = subpassDescriptions,
	};
	PVK_VERIFY(vkCreateRenderPass(gVulkanCore.device, &renderPassCreateInfo, NULL, renderPass));
	return 0;
}

#endif
