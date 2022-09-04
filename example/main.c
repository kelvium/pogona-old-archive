#include <pogona/pogona.h>

int main(void)
{
	loggerInit();
	loggerSetLevel(LOGGER_TRACE);

	WindowError error;
	Window window;
	error = windowCreate(&window, WINDOW_API_TYPE_ANY, 800, 600, "Window");
	if (error != WINDOW_OK) {
		LOGGER_FATAL("could not create window: %d\n", error);
		return 1;
	}

	error = windowDestroy(&window);
	if (error != WINDOW_OK) {
		LOGGER_FATAL("could not destroy window: %d\n", error);
		return 1;
	}
	return 0;
}
