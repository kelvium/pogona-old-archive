#include <pch.h>
#include <pogona/window/wayland_window_api.h>
#include <pogona/window/window.h>

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
	case WINDOW_API_TYPE_WAYLAND: {
#ifdef POGONA_WAYLAND_SUPPORT
		self->api = calloc(1, sizeof(WaylandWindowApi));

		WaylandWindowApiError error = waylandWindowApiCreate((WaylandWindowApi*) self->api, width, height, title);
		if (error != WAYLAND_WINDOW_API_OK)
			return WINDOW_COULD_NOT_CREATE_API;

		break;
#endif
	}
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}

WindowError windowGetApiType(Window* self, WindowApiType* apiType)
{
	switch (self->apiType) {
	case WINDOW_API_TYPE_WAYLAND:
#ifdef POGONA_WAYLAND_SUPPORT
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
	case WINDOW_API_TYPE_WAYLAND: {
#ifdef POGONA_WAYLAND_SUPPORT
		WaylandWindowApiError error = waylandWindowApiGetTitle((WaylandWindowApi*) self->api, title, titleSize);
		if (error != WAYLAND_WINDOW_API_OK)
			return WINDOW_COULD_NOT_GET_TITLE;
#endif
	}
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}

WindowError windowSetTitle(Window* self, const char* title)
{
	switch (self->apiType) {
	case WINDOW_API_TYPE_WAYLAND: {
#ifdef POGONA_WAYLAND_SUPPORT
		WaylandWindowApiError error = waylandWindowApiSetTitle((WaylandWindowApi*) self->api, title);
		if (error != WAYLAND_WINDOW_API_OK)
			return WINDOW_COULD_NOT_SET_TITLE;
#endif
	}
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}

WindowError windowDestroy(Window* self)
{
	switch (self->apiType) {
	case WINDOW_API_TYPE_WAYLAND: {
#ifdef POGONA_WAYLAND_SUPPORT
		WaylandWindowApiError error = waylandWindowApiDestroy((WaylandWindowApi*) self->api);
		if (error != WAYLAND_WINDOW_API_OK)
			return WINDOW_COULD_NOT_DESTROY_API;

		free(self->api);
		break;
#endif
	}
	default:
		return WINDOW_NO_API_AVAILABLE;
	}
	return WINDOW_OK;
}
