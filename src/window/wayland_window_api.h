/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_WAYLAND_SUPPORT

#include <pogona/types.h>
#include <pogona/window.h>
#include <wayland-client.h>

#define WAYLAND_WINDOW_API_TITLE_LENGTH 256

typedef struct WaylandGlobals WaylandGlobals;

typedef struct {
	usize width, height;
	char title[WAYLAND_WINDOW_API_TITLE_LENGTH]; /* the last byte is for NUL */

	WaylandGlobals* waylandGlobals;
} WaylandWindowApi;

i32 waylandWindowApiCreate(WaylandWindowApi* self, usize width, usize height, const char* title);
i32 waylandWindowApiGetTitle(WaylandWindowApi* self, char* title, usize titleSize);
i32 waylandWindowApiSetTitle(WaylandWindowApi* self, const char* title);
i32 waylandWindowApiIsClosed(WaylandWindowApi* self, bool* flag);
i32 waylandWindowApiPollEvents(WaylandWindowApi* self);
i32 waylandWindowApiGetDisplay(WaylandWindowApi* self, struct wl_display** display);
i32 waylandWindowApiGetSurface(WaylandWindowApi* self, struct wl_surface** surface);
i32 waylandWindowApiDestroy(WaylandWindowApi* self);

#endif
