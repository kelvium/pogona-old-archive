/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>
#include <pogona/types.h>

typedef void* WindowApi;

typedef enum {
	WINDOW_API_TYPE_ANY,

#ifdef POGONA_WAYLAND_SUPPORT
	WINDOW_API_TYPE_WAYLAND,
#endif

	WINDOW_API_TYPE_NONE,
} WindowApiType;

const char* windowApiTypeToString(WindowApiType apiType);

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
	WINDOW_COULD_NOT_GET_IS_CLOSED,
} WindowError;

const char* windowErrorToString(WindowError error);

WindowError windowCreate(Window* self, WindowApiType apiType, usize width, usize height, const char* title);
WindowError windowGetApiType(Window* self, WindowApiType* apiType);
WindowError windowGetTitle(Window* self, char* title, usize titleSize);
WindowError windowSetTitle(Window* self, const char* title);
WindowError windowIsClosed(Window* self, bool* flag);
WindowError windowDestroy(Window* self);
