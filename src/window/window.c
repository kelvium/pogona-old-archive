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

const char* windowErrorToString(i32 error)
{
	switch (error) {
	case WINDOW_OK:
		return "Ok";
	case WINDOW_NO_API_AVAILABLE:
		return "No API available";
	case WINDOW_COULD_NOT_CREATE_API:
		return "Could not create API";
	case WINDOW_COULD_NOT_DESTROY_API:
		return "Could not destroy API";
	case WINDOW_COULD_NOT_GET_TITLE:
		return "Could not get title";
	case WINDOW_COULD_NOT_SET_TITLE:
		return "Could not set title";
	case WINDOW_COULD_NOT_GET_IS_CLOSED:
		return "Could not get isClosed()";
	default:
		return "(invalid)";
	}
}

static WindowApiType sDetermineApiType()
{
	// TODO: implement
	return WINDOW_API_TYPE_WAYLAND;
}

i32 windowCreate(Window* self, WindowApiType apiType, usize width, usize height, const char* title)
{
	self->apiType = apiType;
	if (apiType == WINDOW_API_TYPE_ANY) {
		self->apiType = sDetermineApiType();
	}

	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		self->api = calloc(1, sizeof(WaylandWindowApi));

		i32 error = waylandWindowApiCreate((WaylandWindowApi*) self->api, width, height, title);
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

i32 windowGetApiType(Window* self, WindowApiType* apiType)
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

i32 windowGetTitle(Window* self, char* title, usize titleSize)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		i32 error = waylandWindowApiGetTitle((WaylandWindowApi*) self->api, title, titleSize);
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

i32 windowSetTitle(Window* self, const char* title)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		i32 error = waylandWindowApiSetTitle((WaylandWindowApi*) self->api, title);
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

i32 windowIsClosed(Window* self, bool* flag)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		i32 error = waylandWindowApiIsClosed((WaylandWindowApi*) self->api, flag);
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

i32 windowDestroy(Window* self)
{
	switch (self->apiType) {
#ifdef POGONA_WAYLAND_SUPPORT
	case WINDOW_API_TYPE_WAYLAND: {
		i32 error = waylandWindowApiDestroy((WaylandWindowApi*) self->api);
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
