/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <pogona/pogona.h>

int main(void)
{
	loggerInit();
	loggerSetLevel(LOGGER_DEBUG);

	WindowError windowError;
	Window window;
	windowError = windowCreate(&window, WINDOW_API_TYPE_ANY, 800, 600, "Window");
	if (windowError != WINDOW_OK) {
		LOGGER_FATAL("could not create window: %d\n", windowError);
		return 1;
	}
	LOGGER_DEBUG("created a window\n");

	RendererError rendererError;
	Renderer renderer;
	rendererError = rendererCreate(&renderer, RENDERER_API_TYPE_ANY, &window);
	if (rendererError != RENDERER_OK) {
		LOGGER_FATAL("could not create renderer: %d\n", rendererError);
		return 1;
	}
	LOGGER_DEBUG("created a renderer\n");

	bool isClosed = false;
	while (!(isClosed = windowIsClosed(&window, &isClosed))) {
		LOGGER_DEBUG("FRAME\n");
	}

	rendererError = rendererDestroy(&renderer);
	if (rendererError != RENDERER_OK) {
		LOGGER_FATAL("could not destroy renderer: %d\n", rendererError);
		return 1;
	}
	LOGGER_DEBUG("destroyed the renderer\n");

	windowError = windowDestroy(&window);
	if (windowError != WINDOW_OK) {
		LOGGER_FATAL("could not destroy window: %d\n", windowError);
		return 1;
	}
	LOGGER_DEBUG("destroyed the window\n");
	return 0;
}
