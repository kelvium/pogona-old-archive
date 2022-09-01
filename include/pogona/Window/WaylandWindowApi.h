#pragma once

#include <config.h>

#ifdef POGONA_WAYLAND_SUPPORT

#include <pogona/Window/Window.h>
#include <pogona/types.h>

#define WAYLAND_WINDOW_API_TITLE_LENGTH 256

typedef struct {
	usize width, height;
	char title[WAYLAND_WINDOW_API_TITLE_LENGTH]; // the last byte is for NUL
} WaylandWindowApi;

typedef enum {
	WAYLAND_WINDOW_API_OK,
} WaylandWindowApiError;

WaylandWindowApiError waylandWindowApiCreate(
		WaylandWindowApi* self, usize width, usize height, const char* title);
WaylandWindowApiError waylandWindowApiGetTitle(
		WaylandWindowApi* self, char* title, usize titleSize);
WaylandWindowApiError waylandWindowApiSetTitle(
		WaylandWindowApi* self, const char* title);
WaylandWindowApiError waylandWindowApiDestroy(WaylandWindowApi* self);

#endif
