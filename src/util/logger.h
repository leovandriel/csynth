//
// logger.h - Logging
//
#ifndef CSYNTH_LOGGER_H
#define CSYNTH_LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum
{
    LoggerLevelNone = 0,
    LoggerLevelError,
    LoggerLevelWarn,
    LoggerLevelInfo,
    LoggerLevelDebug,
} LoggerLevel;

static const char *LOGGER_LEVEL_STRINGS[] = {
    "NONE",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
};

static volatile LoggerLevel logger_level_global = LoggerLevelInfo;

void logger_set_level(LoggerLevel level)
{
    logger_level_global = level;
}

int logger_log(LoggerLevel level, const char *file, int line, const char *message, ...)
{
    va_list args = {0};
    va_start(args, message);
    struct timespec spec;
    timespec_get(&spec, TIME_UTC);
    char buffer[20];
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", localtime(&spec.tv_sec));
    fprintf(stderr, "\r\e[K%s.%06ld %s %s:%d - ", buffer, spec.tv_nsec / 1000, LOGGER_LEVEL_STRINGS[level], strrchr(file, '/') + 1, line);
    int result = vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
    va_end(args);
    return result;
}

#define log_error(...) (logger_level_global >= LoggerLevelError && logger_log(LoggerLevelError, "/"__FILE__, __LINE__, __VA_ARGS__))
#define log_warn(...) (logger_level_global >= LoggerLevelWarn && logger_log(LoggerLevelWarn, "/"__FILE__, __LINE__, __VA_ARGS__))
#define log_info(...) (logger_level_global >= LoggerLevelInfo && logger_log(LoggerLevelInfo, "/"__FILE__, __LINE__, __VA_ARGS__))
#define log_debug(...) (logger_level_global >= LoggerLevelDebug && logger_log(LoggerLevelDebug, "/"__FILE__, __LINE__, __VA_ARGS__))

#endif // CSYNTH_LOGGER_H
