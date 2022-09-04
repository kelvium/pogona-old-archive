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
	VULKAN_RENDERER_API_REQUIRED_VULKAN_VERSION_IS_NOT_SUPPORTED,
	VULKAN_RENDERER_API_COULD_NOT_CREATE_INSTANCE,
	VULKAN_RENDERER_API_COULD_NOT_PICK_PHYSICAL_DEVICE,
	VULKAN_RENDERER_API_NO_PHYSICAL_DEVICE_GROUPS,
	VULKAN_RENDERER_API_NO_QUEUE_FAMILY_PROPERTIES,
	VULKAN_RENDERER_API_NO_QUEUE_WITH_GRAPHICS_BIT,
	VULKAN_RENDERER_API_COULD_NOT_CREATE_DEVICE,
} VulkanRendererApiError;

VulkanRendererApiError vulkanRendererApiCreate(
		VulkanRendererApi* self, Window* window);
VulkanRendererApiError vulkanRendererApiDestroy(VulkanRendererApi* self);

#endif
