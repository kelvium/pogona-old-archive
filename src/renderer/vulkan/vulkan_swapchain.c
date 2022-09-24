/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "src/renderer/vulkan/vulkan_core.h"
#include "vulkan_swapchain.h"

#include <pch.h>

Swapchain gSwapchain = { 0 };

static VkFormat sPickImageFormat()
{
	u32 formatsCount = gVulkanCore.surface.surfaceFormatsCount;
	VkSurfaceFormatKHR* formats = gVulkanCore.surface.surfaceFormats;

	if (formatsCount == 1 && formats[0].format == VK_FORMAT_UNDEFINED)
		return VK_FORMAT_R8G8B8A8_SRGB;

	for (u32 i = 0; i < formatsCount; ++i) {
		if (formats[i].format == VK_FORMAT_R8G8B8A8_SRGB || formats[i].format == VK_FORMAT_B8G8R8A8_SRGB)
			return formats[i].format;
	}

	return formats[0].format;
}

static VkColorSpaceKHR sPickColorSpace()
{
	u32 formatsCount = gVulkanCore.surface.surfaceFormatsCount;
	VkSurfaceFormatKHR* formats = gVulkanCore.surface.surfaceFormats;

	for (u32 i = 0; i < formatsCount; ++i) {
		if (formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			return formats[i].colorSpace;
	}

	return formats[0].colorSpace;
}

static i32 sRecreateSwapchain(bool force)
{
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	PVK_VERIFY(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
			gVulkanCore.physicalDevice.physicalDevice, gVulkanCore.surface.surface, &surfaceCapabilities));
	u32 newWidth = surfaceCapabilities.currentExtent.width;
	u32 newHeight = surfaceCapabilities.currentExtent.height;

	if (newWidth == gSwapchain.width && newHeight == gSwapchain.height && !force)
		return true;

	gSwapchain.width = 800;
	gSwapchain.height = 600;

	VkSwapchainCreateInfoKHR swapchainCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = gVulkanCore.surface.surface,
		.imageFormat = gSwapchain.imageFormat,
		.imageColorSpace = gSwapchain.colorSpace,
		.presentMode = VK_PRESENT_MODE_FIFO_KHR,
		.oldSwapchain = gSwapchain.swapchain,
		.imageExtent = {
			// FIXME: don't hardcode
			.width = 800,
			.height = 600,
		},
		//.imageExtent = surfaceCapabilities.currentExtent,
		.minImageCount = surfaceCapabilities.minImageCount + 1,
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		.queueFamilyIndexCount = 1,
		.pQueueFamilyIndices = &gVulkanCore.physicalDevice.queueFamilyIndex,
		.preTransform = surfaceCapabilities.currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
	};
	PVK_VERIFY(vkCreateSwapchainKHR(gVulkanCore.device, &swapchainCreateInfo, NULL, &gSwapchain.swapchain));

	PVK_VERIFY(vkGetSwapchainImagesKHR(gVulkanCore.device, gSwapchain.swapchain, &gSwapchain.imagesCount, NULL));
	gSwapchain.images = calloc(gSwapchain.imagesCount, sizeof(VkImage));
	PVK_VERIFY(
			vkGetSwapchainImagesKHR(gVulkanCore.device, gSwapchain.swapchain, &gSwapchain.imagesCount, gSwapchain.images));
	return 0;
}

i32 vulkanSwapchainInitImageViews()
{
	gSwapchain.imageViews = calloc(gSwapchain.imagesCount, sizeof(VkImageView));
	for (u32 i = 0; i < gSwapchain.imagesCount; ++i) {
		VkImageViewCreateInfo imageViewCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = gSwapchain.imageFormat,
			.image = gSwapchain.images[i],
			.subresourceRange = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.levelCount = 1,
				.layerCount = 1,
			},
		};
		PVK_VERIFY(vkCreateImageView(gVulkanCore.device, &imageViewCreateInfo, NULL, gSwapchain.imageViews + i));
	}
	return 0;
}

i32 vulkanSwapchainInitFramebuffers(void)
{
	gSwapchain.framebuffers = calloc(gSwapchain.imagesCount, sizeof(VkFramebuffer));
	for (u32 i = 0; i < gSwapchain.imagesCount; ++i) {
		VkFramebufferCreateInfo framebufferCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.renderPass = gVulkanCore.renderPass,
			.pAttachments = &gSwapchain.imageViews[i],
			.attachmentCount = 1,
			/* FIXME: don't hardcode */
			.width = 800,
			.height = 600,
			.layers = 1,
		};
		PVK_VERIFY(vkCreateFramebuffer(gVulkanCore.device, &framebufferCreateInfo, NULL, gSwapchain.framebuffers + i));
	}
	return 0;
}

i32 vulkanCreateSwapchain(void)
{
	gSwapchain.imageFormat = sPickImageFormat();
	gSwapchain.colorSpace = sPickColorSpace();
	return sRecreateSwapchain(true);
}

i32 vulkanAcquireNextImage(u32* imageIndex, VkSemaphore semaphore)
{
	PVK_VERIFY(vkAcquireNextImageKHR(
			gVulkanCore.device, gSwapchain.swapchain, UINT64_MAX, semaphore, VK_NULL_HANDLE, imageIndex));
	return 0;
}

i32 vulkanDestroySwapchain(void)
{
	for (u32 i = 0; i < gSwapchain.imagesCount; ++i) {
		/* at this point these are created by vulkanSwapchainInitXXX functions, so we can delete them here */
		vkDestroyFramebuffer(gVulkanCore.device, gSwapchain.framebuffers[i], NULL);
		vkDestroyImageView(gVulkanCore.device, gSwapchain.imageViews[i], NULL);
	}
	vkDestroySwapchainKHR(gVulkanCore.device, gSwapchain.swapchain, NULL);
	free(gSwapchain.framebuffers);
	free(gSwapchain.imageViews);
	free(gSwapchain.images);
	return 0;
}

#endif
