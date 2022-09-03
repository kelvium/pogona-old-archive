#pragma once

#include <pogona/types.h>

typedef enum {
	LOGGER_TRACE,
	LOGGER_DEBUG,
	LOGGER_INFO,
	LOGGER_WARNING,
	LOGGER_ERROR,
	LOGGER_FATAL,
} LoggerLevel;

#define LOGGER_DEFAULT_LEVEL LOGGER_INFO

void loggerInit();
void loggerSetLevel(LoggerLevel level);
void loggerLog(LoggerLevel level, const char* sourceFile, usize sourceLine, const char* fmt, ...);

#define LOGGER_TRACE(...) loggerLog(LOGGER_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOGGER_DEBUG(...) loggerLog(LOGGER_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOGGER_INFO(...) loggerLog(LOGGER_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOGGER_WARN(...) loggerLog(LOGGER_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define LOGGER_ERROR(...) loggerLog(LOGGER_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOGGER_FATAL(...) loggerLog(LOGGER_FATAL, __FILE__, __LINE__, __VA_ARGS__)
