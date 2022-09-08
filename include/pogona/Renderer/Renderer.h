#pragma once

#include <pogona/Window/Window.h>
#include <pogona/types.h>

typedef void* RendererApi;

typedef enum {
	RENDERER_API_TYPE_NONE,

	RENDERER_API_TYPE_VULKAN,

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

RendererError rendererCreate(
		Renderer* self, RendererApiType apiType, Window* window);
RendererError rendererDestroy(Renderer* self);
