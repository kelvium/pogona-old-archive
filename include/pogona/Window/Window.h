#pragma once

#include <config.h>
#include <pogona/types.h>

typedef void* WindowApi;

typedef enum {
	WINDOW_API_TYPE_ANY,

	WINDOW_API_TYPE_WAYLAND,

	WINDOW_API_TYPE_NONE,
} WindowApiType;

typedef struct {
	WindowApi api;
	WindowApiType apiType;
} Window;

typedef enum {
	WINDOW_OK,
	WINDOW_NO_API_AVAILABLE,
	WINDOW_COULD_NOT_CREATE_API,
	WINDOW_COULD_NOT_DESTROY_API,
	WINDOW_COULD_NOT_GET_TITLE,
	WINDOW_COULD_NOT_SET_TITLE,
} WindowError;

WindowError windowCreate(Window* self, WindowApiType apiType, usize width, usize height, const char* title);
WindowError windowGetApiType(Window* window, WindowApiType* apiType);
WindowError windowGetTitle(Window* window, char* title, usize titleSize);
WindowError windowSetTitle(Window* window, const char* title);
WindowError windowDestroy(Window* window);
