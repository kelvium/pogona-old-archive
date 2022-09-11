/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_WAYLAND_SUPPORT

#include "wayland_window_api.h"

#include <pch.h>
#include <pogona/logger.h>
#include <wayland-client.h>
#include <xdg-shell-client-protocol.h>

typedef struct WaylandGlobals {
	struct wl_display* display;
	struct wl_registry* registry;
	struct wl_compositor* compositor;
	struct wl_surface* surface;
	struct xdg_wm_base* xdgWmBase;
	struct xdg_surface* xdgSurface;
	struct xdg_toplevel* xdgToplevel;
} WaylandGlobals;

static void sRegistryGlobal(void* data, struct wl_registry* registry, u32 name, const char* interface, u32 version)
{
	WaylandGlobals* globals = (WaylandGlobals*) data;

	if (strcmp(interface, wl_compositor_interface.name) == 0) {
		globals->compositor = wl_registry_bind(registry, name, &wl_compositor_interface, version);
		LOGGER_DEBUG("got wl_compositor\n");
		return;
	}
	if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
		globals->xdgWmBase = wl_registry_bind(registry, name, &xdg_wm_base_interface, version);
		LOGGER_DEBUG("got xdg_wm_base\n");
		return;
	}
}

static void sXdgWmBasePing(void* data, struct xdg_wm_base* xdgWmBase, u32 serial)
{
	(void) data;
	xdg_wm_base_pong(xdgWmBase, serial);
}

WaylandWindowApiError waylandWindowApiCreate(WaylandWindowApi* self, usize width, usize height, const char* title)
{
	self->width = width;
	self->height = height;
	strncpy(self->title, title, WAYLAND_WINDOW_API_TITLE_LENGTH);
	self->waylandGlobals = calloc(1, sizeof(WaylandGlobals));

	// connect to display
	self->waylandGlobals->display = wl_display_connect(NULL);
	if (!self->waylandGlobals->display) {
		LOGGER_ERROR("could not connect to display\n");
		return WAYLAND_WINDOW_API_COULD_NOT_CONNECT_TO_DISPLAY;
	}
	LOGGER_DEBUG("connected to display\n");

	// get a registry && get required protocols from it
	static const struct wl_registry_listener sRegistryListener = {
		.global = sRegistryGlobal,
		.global_remove = NULL,
	};
	self->waylandGlobals->registry = wl_display_get_registry(self->waylandGlobals->display);
	if (!self->waylandGlobals->registry) {
		LOGGER_ERROR("could not get registry\n");
		return WAYLAND_WINDOW_API_COULD_NOT_GET_REGISTRY;
	}
	LOGGER_DEBUG("got registry\n");
	wl_registry_add_listener(self->waylandGlobals->registry, &sRegistryListener, (void*) self->waylandGlobals);
	wl_display_dispatch(self->waylandGlobals->display);
	wl_display_roundtrip(self->waylandGlobals->display);

	// create a surface
	self->waylandGlobals->surface = wl_compositor_create_surface(self->waylandGlobals->compositor);
	if (!self->waylandGlobals->surface) {
		LOGGER_ERROR("could not create a surface\n");
		return WAYLAND_WINDOW_API_COULD_NOT_CREATE_SURFACE;
	}
	LOGGER_DEBUG("created a surface\n");

	// add a ping-pong listener to xdg_wm_base
	static const struct xdg_wm_base_listener sXdgWmBaseListener = {
		.ping = sXdgWmBasePing,
	};
	xdg_wm_base_add_listener(self->waylandGlobals->xdgWmBase, &sXdgWmBaseListener, (void*) self->waylandGlobals);

	// create an xdg_surface from the surface
	self->waylandGlobals->xdgSurface
			= xdg_wm_base_get_xdg_surface(self->waylandGlobals->xdgWmBase, self->waylandGlobals->surface);
	if (!self->waylandGlobals->xdgSurface) {
		LOGGER_ERROR("could not get an xdg_surface\n");
		return WAYLAND_WINDOW_API_COULD_NOT_GET_XDG_SURFACE;
	}
	LOGGER_DEBUG("got an xdg_surface\n");

	// get an xdg_toplevel from the xdg_surface
	self->waylandGlobals->xdgToplevel = xdg_surface_get_toplevel(self->waylandGlobals->xdgSurface);
	if (!self->waylandGlobals->xdgToplevel) {
		LOGGER_ERROR("could not get an xdg_toplevel\n");
		return WAYLAND_WINDOW_API_COULD_NOT_GET_XDG_TOPLEVEL;
	}
	LOGGER_DEBUG("got an xdg_toplevel\n");

	// set xdg_toplevel properties
	xdg_toplevel_set_min_size(self->waylandGlobals->xdgToplevel, self->width, self->height);
	xdg_toplevel_set_max_size(self->waylandGlobals->xdgToplevel, self->width, self->height);
	xdg_toplevel_set_title(self->waylandGlobals->xdgToplevel, self->title);
	return WAYLAND_WINDOW_API_OK;
}

WaylandWindowApiError waylandWindowApiGetTitle(WaylandWindowApi* self, char* title, usize titleSize)
{
	strncpy(title, self->title, titleSize);
	return WAYLAND_WINDOW_API_OK;
}

WaylandWindowApiError waylandWindowApiSetTitle(WaylandWindowApi* self, const char* title)
{
	strncpy(self->title, title, WAYLAND_WINDOW_API_TITLE_LENGTH);
	xdg_toplevel_set_title(self->waylandGlobals->xdgToplevel, self->title);
	return WAYLAND_WINDOW_API_OK;
}

WaylandWindowApiError waylandWindowApiGetSurface(WaylandWindowApi* self, struct wl_surface** surface)
{
	*surface = self->waylandGlobals->surface;
	return WAYLAND_WINDOW_API_OK;
}

WaylandWindowApiError waylandWindowApiDestroy(WaylandWindowApi* self)
{
	xdg_toplevel_destroy(self->waylandGlobals->xdgToplevel);
	LOGGER_DEBUG("destroyed xdg_toplevel\n");

	xdg_surface_destroy(self->waylandGlobals->xdgSurface);
	LOGGER_DEBUG("destroyed xdg_surface\n");

	xdg_wm_base_destroy(self->waylandGlobals->xdgWmBase);
	LOGGER_DEBUG("destroyed xdg_wm_base\n");

	wl_surface_destroy(self->waylandGlobals->surface);
	LOGGER_DEBUG("destroyed surface\n");

	wl_registry_destroy(self->waylandGlobals->registry);
	LOGGER_DEBUG("destroyed registry\n");

	wl_compositor_destroy(self->waylandGlobals->compositor);
	LOGGER_DEBUG("destroyed compositor\n");

	wl_display_disconnect(self->waylandGlobals->display);
	LOGGER_DEBUG("disconnected from display\n");

	free(self->waylandGlobals);
	return WAYLAND_WINDOW_API_OK;
}

#endif
