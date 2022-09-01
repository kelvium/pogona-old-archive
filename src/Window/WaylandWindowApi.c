#include <config.h>

#ifdef POGONA_WAYLAND_SUPPORT

#include <pch.h>
#include <pogona/Window/WaylandWindowApi.h>

WaylandWindowApiError waylandWindowApiCreate(
		WaylandWindowApi* self, usize width, usize height, const char* title)
{
	self->width = width;
	self->height = height;
	strncpy(self->title, title, WAYLAND_WINDOW_API_TITLE_LENGTH);

	// TODO: implement
	return WAYLAND_WINDOW_API_OK;
}

WaylandWindowApiError waylandWindowApiGetTitle(WaylandWindowApi *self, char *title, usize titleSize)
{
	(void) self;
	(void) title;
	(void) titleSize;

	// TODO: implement
	return WAYLAND_WINDOW_API_OK;
}

WaylandWindowApiError waylandWindowApiSetTitle(WaylandWindowApi *self, const char *title)
{
	(void) self;
	(void) title;

	// TODO: implement
	return WAYLAND_WINDOW_API_OK;
}

WaylandWindowApiError waylandWindowApiDestroy(WaylandWindowApi* self)
{
	(void) self;

	// TODO: implement
	return WAYLAND_WINDOW_API_OK;
}

#endif
