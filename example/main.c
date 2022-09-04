#include "pogona/Renderer/Renderer.h"

#include <pogona/pogona.h>

int main(void)
{
	loggerInit();
	loggerSetLevel(LOGGER_TRACE);

	WindowError windowError;
	Window window;
	windowError = windowCreate(&window, WINDOW_API_TYPE_ANY, 800, 600, "Window");
	if (windowError != WINDOW_OK) {
		LOGGER_FATAL("could not create window: %d\n", windowError);
		return 1;
	}
	LOGGER_TRACE("created a window\n");

	RendererError rendererError;
	Renderer renderer;
	rendererError = rendererCreate(&renderer, RENDERER_API_TYPE_VULKAN, &window);
	if (rendererError != RENDERER_OK) {
		LOGGER_FATAL("could not create renderer: %d\n", rendererError);
		return 1;
	}
	LOGGER_TRACE("created a renderer\n");

	rendererError = rendererDestroy(&renderer);
	if (rendererError != RENDERER_OK) {
		LOGGER_FATAL("could not destroy renderer: %d\n", rendererError);
		return 1;
	}
	LOGGER_TRACE("destroyed the renderer\n");

	windowError = windowDestroy(&window);
	if (windowError != WINDOW_OK) {
		LOGGER_FATAL("could not destroy window: %d\n", windowError);
		return 1;
	}
	LOGGER_TRACE("destroyed the window\n");
	return 0;
}
