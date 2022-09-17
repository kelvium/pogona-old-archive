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
	if (error < 0) {
		LOGGER_FATAL("could not create window\n");
		return 1;
	}

	Renderer renderer;
	error = rendererCreate(&renderer, RENDERER_API_TYPE_ANY, &window);
	if (error < 0) {
		LOGGER_FATAL("could not create renderer\n");
		return 1;
	}

	bool isClosed = false;
	while (!isClosed) {
		rendererDraw(&renderer);
		windowPollEvents(&window);
		isClosed = windowIsClosed(&window, &isClosed);
	}

	error = rendererDestroy(&renderer);
	if (error < 0) {
		LOGGER_FATAL("could not destroy renderer\n");
		return 1;
	}

	error = windowDestroy(&window);
	if (error < 0) {
		LOGGER_FATAL("could not destroy window\n");
		return 1;
	}
	return 0;
}
