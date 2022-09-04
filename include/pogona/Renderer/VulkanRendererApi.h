#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pogona/Window/Window.h>

#ifdef POGONA_WAYLAND_SUPPORT
#define VK_USE_PLATFORM_WAYLAND_KHR
#endif
#include <volk.h>

typedef struct {
	Window* window;
} VulkanRendererApi;

typedef enum {
	VULKAN_RENDERER_API_OK,
} VulkanRendererApiError;

VulkanRendererApiError vulkanRendererApiCreate(VulkanRendererApi* self, Window* window);
VulkanRendererApiError vulkanRendererApiDestroy(VulkanRendererApi* self);

#endif
