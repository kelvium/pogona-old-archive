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

const char* rendererErrorToString(i32 error)
{
	switch (error) {
	case RENDERER_OK:
		return "Ok";
	case RENDERER_NO_API_AVAILABLE:
		return "No API available";
	case RENDERER_COULD_NOT_CREATE_API:
		return "Could not create API";
	case RENDERER_COULD_NOT_DESTROY_API:
		return "Could not destroy API";
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
		if (error != VULKAN_RENDERER_API_OK) {
			LOGGER_ERROR("could not create a renderer api\n");
			return RENDERER_COULD_NOT_CREATE_API;
		}
		break;
	}
#endif
	default: {
		LOGGER_ERROR("no api available\n");
		return RENDERER_NO_API_AVAILABLE;
	}
	}
	LOGGER_DEBUG("created an api\n");
	return RENDERER_OK;
}

i32 rendererDestroy(Renderer* self)
{
	switch (self->apiType) {
#ifdef POGONA_VULKAN_SUPPORT
	case RENDERER_API_TYPE_VULKAN: {
		i32 error = vulkanRendererApiDestroy((VulkanRendererApi*) self->api);
		if (error != VULKAN_RENDERER_API_OK) {
			LOGGER_ERROR("could not destroy renderer api\n");
			return RENDERER_COULD_NOT_DESTROY_API;
		}
		break;
	}
#endif
	default: {
		LOGGER_ERROR("no api available\n");
		return RENDERER_NO_API_AVAILABLE;
	}
	}
	free(self->api);
	LOGGER_DEBUG("destroyed the api\n");
	return RENDERER_OK;
}
