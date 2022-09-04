#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pch.h>
#include <pogona/Renderer/VulkanRendererApi.h>

VulkanRendererApiError vulkanRendererApiCreate(
		VulkanRendererApi* self, Window* window)
{
	self->window = window;

	// TODO: implement
	return VULKAN_RENDERER_API_OK;
}

VulkanRendererApiError vulkanRendererApiDestroy(VulkanRendererApi* self)
{
	(void) self;

	// TODO: implement
	return VULKAN_RENDERER_API_OK;
}

#endif
