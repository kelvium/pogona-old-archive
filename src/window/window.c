/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "wayland_window_api.h"

#include <pch.h>
#include <pogona/window.h>

static WindowApiType sDetermineApiType()
{
	// TODO: implement
	return WINDOW_API_TYPE_WAYLAND;
}

WindowError windowCreate(Window* self, WindowApiType apiType, usize width, usize height, const char* title)
{
	self->apiType = apiType;
	if (apiType == WINDOW_API_TYPE_ANY) {
		self->apiType = sDetermineApiType();
	}

	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		self->api = calloc(1, sizeof(WaylandWindowApi));

		WaylandWindowApiError error = waylandWindowApiCreate((WaylandWindowApi*) self->api, width, height, title);
		if (error != WAYLAND_WINDOW_API_OK)
			return WINDOW_COULD_NOT_CREATE_API;

		break;
	}
#endif
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}

WindowError windowGetApiType(Window* self, WindowApiType* apiType)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND:
		*apiType = self->apiType;
#endif
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}

WindowError windowGetTitle(Window* self, char* title, usize titleSize)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		WaylandWindowApiError error = waylandWindowApiGetTitle((WaylandWindowApi*) self->api, title, titleSize);
		if (error != WAYLAND_WINDOW_API_OK)
			return WINDOW_COULD_NOT_GET_TITLE;
		break;
	}
#endif
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}

WindowError windowSetTitle(Window* self, const char* title)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		WaylandWindowApiError error = waylandWindowApiSetTitle((WaylandWindowApi*) self->api, title);
		if (error != WAYLAND_WINDOW_API_OK)
			return WINDOW_COULD_NOT_SET_TITLE;
		break;
	}
#endif
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}

WindowError windowIsClosed(Window* self, bool* flag)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		WaylandWindowApiError error = waylandWindowApiIsClosed((WaylandWindowApi*) self->api, flag);
		if (error != WAYLAND_WINDOW_API_OK)
			return WINDOW_COULD_NOT_GET_IS_CLOSED;
		break;
	}
#endif
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}

WindowError windowDestroy(Window* self)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		WaylandWindowApiError error = waylandWindowApiDestroy((WaylandWindowApi*) self->api);
		if (error != WAYLAND_WINDOW_API_OK)
			return WINDOW_COULD_NOT_DESTROY_API;

		free(self->api);
		break;
	}
#endif
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}
