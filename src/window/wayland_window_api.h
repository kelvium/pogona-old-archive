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

typedef enum {
	WAYLAND_WINDOW_API_OK,
	WAYLAND_WINDOW_API_COULD_NOT_CONNECT_TO_DISPLAY,
	WAYLAND_WINDOW_API_COULD_NOT_GET_REGISTRY,
	WAYLAND_WINDOW_API_COULD_NOT_CREATE_SURFACE,
	WAYLAND_WINDOW_API_COULD_NOT_GET_XDG_SURFACE,
	WAYLAND_WINDOW_API_COULD_NOT_GET_XDG_TOPLEVEL,
} WaylandWindowApiError;

WaylandWindowApiError waylandWindowApiCreate(WaylandWindowApi* self, usize width, usize height, const char* title);
WaylandWindowApiError waylandWindowApiGetTitle(WaylandWindowApi* self, char* title, usize titleSize);
WaylandWindowApiError waylandWindowApiSetTitle(WaylandWindowApi* self, const char* title);
WaylandWindowApiError waylandWindowApiGetSurface(WaylandWindowApi* self, struct wl_surface** surface);
WaylandWindowApiError waylandWindowApiDestroy(WaylandWindowApi* self);

#endif
