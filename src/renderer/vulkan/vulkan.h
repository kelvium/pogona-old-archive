#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#ifdef POGONA_WAYLAND_SUPPORT
#define VK_USE_PLATFORM_WAYLAND_KHR
#endif
#include <volk.h>

typedef struct {
	VkInstance instance;
	VkPhysicalDevice physicalDevice;
	VkDevice device;
} VulkanGlobals;

#endif
