/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <pogona/types.h>
#include <pogona/window.h>

typedef void* RendererApi;

typedef enum {
	RENDERER_API_TYPE_NONE,

#ifdef POGONA_VULKAN_SUPPORT
	RENDERER_API_TYPE_VULKAN,
#endif

	RENDERER_API_TYPE_ANY,
} RendererApiType;

typedef struct {
	Window* window;
	RendererApi api;
	RendererApiType apiType;
} Renderer;

typedef enum {
	RENDERER_OK,
	RENDERER_NO_API_AVAILABLE,
	RENDERER_COULD_NOT_CREATE_API,
	RENDERER_COULD_NOT_DESTROY_API,
} RendererError;

RendererError rendererCreate(Renderer* self, RendererApiType apiType, Window* window);
RendererError rendererDestroy(Renderer* self);
