/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <pogona/pogona.h>

int main(void)
{
	i32 error;
	loggerInit();
	loggerSetLevel(LOGGER_DEBUG);

	Window window;
	error = windowCreate(&window, WINDOW_API_TYPE_ANY, 800, 600, "Window");
	if (error != WINDOW_OK) {
		LOGGER_FATAL("could not create window: %s\n", windowErrorToString(error));
		return 1;
	}

	Renderer renderer;
	error = rendererCreate(&renderer, RENDERER_API_TYPE_ANY, &window);
	if (error != RENDERER_OK) {
		LOGGER_FATAL("could not create renderer: %d\n", rendererErrorToString(error));
		return 1;
	}

	bool isClosed = false;
	while (!(isClosed = windowIsClosed(&window, &isClosed))) {
		LOGGER_DEBUG("FRAME\n");
	}

	error = rendererDestroy(&renderer);
	if (error != RENDERER_OK) {
		LOGGER_FATAL("could not destroy renderer: %d\n", rendererErrorToString(error));
		return 1;
	}

	error = windowDestroy(&window);
	if (error != WINDOW_OK) {
		LOGGER_FATAL("could not destroy window: %s\n", windowErrorToString(error));
		return 1;
	}
	return 0;
}
