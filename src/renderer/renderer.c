/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>
#include <pch.h>
#include <pogona/logger.h>
#include <pogona/renderer.h>

#ifdef POGONA_VULKAN_SUPPORT
#include "vulkan_renderer_api.h"
#endif

const char* rendererApiTypeToString(RendererApiType apiType)
{
	switch (apiType) {
	case RENDERER_API_TYPE_ANY:
		return "Any";
#ifdef POGONA_VULKAN_SUPPORT
	case RENDERER_API_TYPE_VULKAN:
		return "Vulkan";
#endif
	case RENDERER_API_TYPE_NONE:
		return "None";
	default:
		return "(invalid)";
	}
}

static RendererApiType sRendererChooseApiType()
{
	// TODO: implement
	return RENDERER_API_TYPE_VULKAN;
}

i32 rendererCreate(Renderer* self, RendererApiType apiType, Window* window)
{
	self->apiType = apiType;
	if (self->apiType == RENDERER_API_TYPE_ANY) {
		self->apiType = sRendererChooseApiType();
		LOGGER_WARN("renderer api type was not specified, chose %s\n", rendererApiTypeToString(self->apiType));
	}
	self->window = window;

	switch (self->apiType) {
#ifdef POGONA_VULKAN_SUPPORT
	case RENDERER_API_TYPE_VULKAN: {
		self->api = calloc(1, sizeof(VulkanRendererApi));
		i32 error = vulkanRendererApiCreate(self->api, self->window);
		if (error < 0) {
			LOGGER_ERROR("could not create a renderer api\n");
			return -1;
		}
		break;
	}
#endif
	default: {
		LOGGER_ERROR("no api available\n");
		return -1;
	}
	}
	return 0;
}

i32 rendererDraw(Renderer* self)
{
	switch (self->apiType) {
#ifdef POGONA_VULKAN_SUPPORT
	case RENDERER_API_TYPE_VULKAN: {
		i32 error = vulkanRendererApiDraw(self->api);
		if (error < 0) {
			LOGGER_ERROR("could not draw with vulkan\n");
			return -1;
		}
		break;
	}
#endif
	default:
		return -1;
	}
	return 0;
}

i32 rendererDestroy(Renderer* self)
{
	switch (self->apiType) {
#ifdef POGONA_VULKAN_SUPPORT
	case RENDERER_API_TYPE_VULKAN: {
		i32 error = vulkanRendererApiDestroy((VulkanRendererApi*) self->api);
		if (error < 0) {
			LOGGER_ERROR("could not destroy renderer api\n");
			return -1;
		}
		break;
	}
#endif
	default: {
		LOGGER_ERROR("no api available\n");
		return -1;
	}
	}
	free(self->api);
	return 0;
}
