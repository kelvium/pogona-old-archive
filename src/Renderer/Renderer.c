#include <config.h>
#include <pch.h>
#include <pogona/Renderer/Renderer.h>
#include <pogona/logger.h>

#ifdef POGONA_VULKAN_SUPPORT
#include <pogona/Renderer/VulkanRendererApi.h>
#endif

static RendererApiType sRendererChooseApiType()
{
	// TODO: implement
	return RENDERER_API_TYPE_VULKAN;
}

RendererError rendererCreate(Renderer* self, RendererApiType apiType, Window* window)
{
	self->apiType = apiType;
	if (self->apiType == RENDERER_API_TYPE_ANY) {
		self->apiType = sRendererChooseApiType();
		LOGGER_WARN("renderer api type was not specified, chose %d\n", self->apiType);
	}
	self->window = window;

	switch (self->apiType) {
	case RENDERER_API_TYPE_VULKAN: {
#ifdef POGONA_VULKAN_SUPPORT
		self->api = calloc(1, sizeof(VulkanRendererApi));
		VulkanRendererApiError error = vulkanRendererApiCreate(self->api, self->window);
		if (error != VULKAN_RENDERER_API_OK) {
			LOGGER_ERROR("could not create a renderer api\n");
			return RENDERER_COULD_NOT_CREATE_API;
		}
		break;
#endif
	}
	default: {
		LOGGER_ERROR("no api available\n");
		return RENDERER_NO_API_AVAILABLE;
	}
	}
	LOGGER_TRACE("created an api\n");
	return RENDERER_OK;
}

RendererError rendererDestroy(Renderer* self)
{
	switch (self->apiType) {
	case RENDERER_API_TYPE_VULKAN: {
#ifdef POGONA_VULKAN_SUPPORT
		VulkanRendererApiError error = vulkanRendererApiDestroy((VulkanRendererApi*) self->api);
		if (error != VULKAN_RENDERER_API_OK) {
			LOGGER_ERROR("could not destroy renderer api\n");
			return RENDERER_COULD_NOT_DESTROY_API;
		}
		break;
#endif
	}
	default: {
		LOGGER_ERROR("no api available\n");
		return RENDERER_NO_API_AVAILABLE;
	}
	}
	free(self->api);
	LOGGER_TRACE("destroyed the api\n");
	return RENDERER_OK;
}
