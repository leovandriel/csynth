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
    LoggerLevelError = 1,
    LoggerLevelWarn = 2,
    LoggerLevelInfo = 3,
    LoggerLevelDebug = 4,
} LoggerLevel;

static const char *logger_level_strings[] = {
    "NONE",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
};

static volatile int logger_level = LoggerLevelInfo;

void logger_set_level(LoggerLevel level)
{
    logger_level = level;
}

int logger_log(LoggerLevel level, const char *file, int line, const char *message, ...)
{
    va_list args = {0};
    va_start(args, message);
    struct timespec spec;
    timespec_get(&spec, TIME_UTC);
    char buffer[20];
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", localtime(&spec.tv_sec));
    fprintf(stderr, "\r\e[K%s.%06ld %s %s:%d - ", buffer, spec.tv_nsec / 1000, logger_level_strings[level], strrchr(file, '/') + 1, line);
    int result = vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
    va_end(args);
    return result;
}

#define log_error(...) (logger_level >= LoggerLevelError && logger_log(LoggerLevelError, "/"__FILE__, __LINE__, __VA_ARGS__))
#define log_warn(...) (logger_level >= LoggerLevelWarn && logger_log(LoggerLevelWarn, "/"__FILE__, __LINE__, __VA_ARGS__))
#define log_info(...) (logger_level >= LoggerLevelInfo && logger_log(LoggerLevelInfo, "/"__FILE__, __LINE__, __VA_ARGS__))
#define log_debug(...) (logger_level >= LoggerLevelDebug && logger_log(LoggerLevelDebug, "/"__FILE__, __LINE__, __VA_ARGS__))

#endif // CSYNTH_LOGGER_H
