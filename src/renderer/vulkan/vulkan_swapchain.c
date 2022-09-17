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

static struct {
	u32 width, height;

	VkSwapchainKHR swapchain;
	VkFormat imageFormat;
} sSwapchain = { 0 };

static i32 sRecreateSwapchain(bool force)
{
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	PVK_VERIFY(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
			gVulkanCore.physicalDevice.physicalDevice, gVulkanCore.surface.surface, &surfaceCapabilities));
	u32 newWidth = surfaceCapabilities.currentExtent.width;
	u32 newHeight = surfaceCapabilities.currentExtent.height;

	if (newWidth == sSwapchain.width && newHeight == sSwapchain.height && !force)
		return true;

	sSwapchain.width = newWidth;
	sSwapchain.height = newHeight;

	/* FIXME: vkGetPhysicalDeviceSurfaceFormatsKHR, etc..? */
	VkSwapchainCreateInfoKHR swapchainCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = gVulkanCore.surface.surface,
		.imageFormat = sSwapchain.imageFormat,
		.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
		.presentMode = VK_PRESENT_MODE_FIFO_KHR,
		.oldSwapchain = sSwapchain.swapchain,
		.imageExtent = {
			// FIXME: don't hardcode
			.width = 800,
			.height = 600,
		},
		//.imageExtent = surfaceCapabilities.currentExtent,
		.minImageCount = surfaceCapabilities.minImageCount + 1,
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.queueFamilyIndexCount = 1,
		.pQueueFamilyIndices = &gVulkanCore.physicalDevice.queueFamilyIndex,
		.preTransform = surfaceCapabilities.currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
	};
	PVK_VERIFY(vkCreateSwapchainKHR(gVulkanCore.device, &swapchainCreateInfo, NULL, &sSwapchain.swapchain));
	return 0;
}

i32 vulkanCreateSwapchain(void)
{
	sSwapchain.imageFormat = VK_FORMAT_R8G8B8A8_SRGB;
	return sRecreateSwapchain(true);
}

i32 vulkanDestroySwapchain(void)
{
	vkDestroySwapchainKHR(gVulkanCore.device, sSwapchain.swapchain, NULL);
	return 0;
}

#endif
