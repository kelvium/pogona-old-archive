#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pogona/Window/Window.h>

#ifdef POGONA_WAYLAND_SUPPORT
#define VK_USE_PLATFORM_WAYLAND_KHR
#endif
#include <volk.h>

typedef struct VulkanGlobals VulkanGlobals;

typedef struct {
	Window* window;
	VulkanGlobals* vulkanGlobals;
} VulkanRendererApi;

typedef enum {
	VULKAN_RENDERER_API_OK,
	VULKAN_RENDERER_REQUIRED_VULKAN_VERSION_IS_NOT_SUPPORTED,
	VULKAN_RENDERER_COULD_NOT_CREATE_INSTANCE,
} VulkanRendererApiError;

VulkanRendererApiError vulkanRendererApiCreate(
		VulkanRendererApi* self, Window* window);
VulkanRendererApiError vulkanRendererApiDestroy(VulkanRendererApi* self);

#endif
