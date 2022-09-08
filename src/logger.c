#include <pch.h>
#include <pogona/logger.h>
#include <stdarg.h>
#include <time.h>

static struct {
	LoggerLevel level;
	struct tm* time;
} sLogger = {
	.level = LOGGER_DEFAULT_LEVEL,
	.time = NULL,
};

static const char* sLevelStrings[] = { "TRACE", "DEBUG", "INFO", "WARNING", "ERROR", "FATAL" };

static const char* sLevelColours[] = { "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m" };

void loggerInit()
{
	{
		time_t rawTime = time(NULL);
		sLogger.time = localtime(&rawTime);
	}
}

void loggerLog(LoggerLevel level, const char* sourceFile, usize sourceLine, const char* fmt, ...)
{
	if (level < sLogger.level)
		return;

	va_list ap;
	va_start(ap, fmt);

	char buffer[16] = { 0 };
	buffer[strftime(buffer, sizeof(buffer), "%H:%M:%S", sLogger.time)] = 0;
	printf("%s %s%-7s\x1b[0m \x1b[90m%s:%zu:\x1b[0m ", buffer, sLevelColours[level], sLevelStrings[level], sourceFile,
			sourceLine);
	vprintf(fmt, ap);

	va_end(ap);
}

void loggerSetLevel(LoggerLevel level) { sLogger.level = level; }
