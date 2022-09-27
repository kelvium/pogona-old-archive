/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <pogona/math/linear.h>

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

i32 windowCreate(Window* self, WindowApiType apiType, Vec2u32 resolution, const char* title);
i32 windowGetApiType(Window* self, WindowApiType* apiType);
i32 windowGetTitle(Window* self, char* title, usize titleSize);
i32 windowSetTitle(Window* self, const char* title);
i32 windowIsClosed(Window* self, bool* flag);
i32 windowPollEvents(Window* self);
i32 windowDestroy(Window* self);

#ifdef __cplusplus
}
#endif
