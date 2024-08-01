#ifndef CSYNTH_LOGGER_H
#define CSYNTH_LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum
{
    LoggerLevelNone = 0,
    LoggerLevelDebug,
    LoggerLevelInfo,
    LoggerLevelWarn,
    LoggerLevelError,
    LoggerLevelMute,
} LoggerLevel;

static const char *LOGGER_LEVEL_STRINGS[] = {
    "NONE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "MUTE",
};

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

typedef int (*logger_cb)(LoggerLevel level, const char *file, int line, const char *message, ...);

static volatile LoggerLevel logger_level_global = LoggerLevelInfo;
static volatile logger_cb logger_cb_global = logger_log;

void logger_set_level(LoggerLevel level)
{
    logger_level_global = level;
}

#define log_error_expr(...) (logger_level_global <= LoggerLevelError && logger_cb_global(LoggerLevelError, "/"__FILE__, __LINE__, __VA_ARGS__))
#define log_warn_expr(...) (logger_level_global <= LoggerLevelWarn && logger_cb_global(LoggerLevelWarn, "/"__FILE__, __LINE__, __VA_ARGS__))
#define log_info_expr(...) (logger_level_global <= LoggerLevelInfo && logger_cb_global(LoggerLevelInfo, "/"__FILE__, __LINE__, __VA_ARGS__))
#define log_debug_expr(...) (logger_level_global <= LoggerLevelDebug && logger_cb_global(LoggerLevelDebug, "/"__FILE__, __LINE__, __VA_ARGS__))

#define log_error(...) (void)log_error_expr(__VA_ARGS__)
#define log_warn(...) (void)log_warn_expr(__VA_ARGS__)
#define log_info(...) (void)log_info_expr(__VA_ARGS__)
#define log_debug(...) (void)log_debug_expr(__VA_ARGS__)

#endif // CSYNTH_LOGGER_H
