/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "wayland_window_api.h"

#include <pch.h>
#include <pogona/window.h>

const char* windowApiTypeToString(WindowApiType apiType)
{
	switch (apiType) {
	case WINDOW_API_TYPE_ANY:
		return "Any";
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND:
		return "Wayland";
#endif
	case WINDOW_API_TYPE_NONE:
		return "None";
	default:
		return "(invalid)";
	}
}

static WindowApiType sDetermineApiType()
{
	// TODO: implement
	return WINDOW_API_TYPE_WAYLAND;
}

i32 windowCreate(Window* self, WindowApiType apiType, Vec2u32 resolution, const char* title)
{
	self->apiType = apiType;
	if (apiType == WINDOW_API_TYPE_ANY) {
		self->apiType = sDetermineApiType();
	}

	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		self->api = calloc(1, sizeof(WaylandWindowApi));

		i32 error = waylandWindowApiCreate((WaylandWindowApi*) self->api, resolution, title);
		if (error < 0)
			return -1;
		break;
	}
#endif
	default:
		return -1;
	}
	return 0;
}

i32 windowGetApiType(Window* self, WindowApiType* apiType)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND:
		*apiType = self->apiType;
#endif
	default:
		return -1;
	}
	return 0;
}

i32 windowGetTitle(Window* self, char* title, usize titleSize)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		i32 error = waylandWindowApiGetTitle((WaylandWindowApi*) self->api, title, titleSize);
		if (error < 0)
			return -1;
		break;
	}
#endif
	default:
		return -1;
	}
	return 0;
}

i32 windowSetTitle(Window* self, const char* title)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		i32 error = waylandWindowApiSetTitle((WaylandWindowApi*) self->api, title);
		if (error < 0)
			return -1;
		break;
	}
#endif
	default:
		return -1;
	}
	return 0;
}

i32 windowIsClosed(Window* self, bool* flag)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		i32 error = waylandWindowApiIsClosed((WaylandWindowApi*) self->api, flag);
		if (error < 0)
			return -1;
		break;
	}
#endif
	default:
		return -1;
	}
	return -1;
}

i32 windowPollEvents(Window* self)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		i32 error = waylandWindowApiPollEvents((WaylandWindowApi*) self->api);
		if (error < 0)
			return -1;
		break;
	}
#endif
	default:
		return -1;
	}
	return -1;
}

i32 windowDestroy(Window* self)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		i32 error = waylandWindowApiDestroy((WaylandWindowApi*) self->api);
		if (error < 0)
			return -1;

		free(self->api);
		break;
	}
#endif
	default:
		return -1;
	}
	return 0;
}
