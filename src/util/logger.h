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

int logger_format_default(FILE *file, LoggerLevel level, const char *source, int line, const char *message, ...)
{
    va_list args = {0};
    va_start(args, message);
    struct timespec spec;
    timespec_get(&spec, TIME_UTC);
    char buffer[20];
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", localtime(&spec.tv_sec));
    fprintf(file, "\r\e[K%s.%06ld %s %s:%d - ", buffer, spec.tv_nsec / 1000, LOGGER_LEVEL_STRINGS[level], strrchr(source, '/') + 1, line);
    int result = vfprintf(file, message, args);
    fprintf(file, "\n");
    va_end(args);
    return result;
}

#define LOGGER_FILE_DEFAULT stderr
#define LOGGER_LEVEL_DEFAULT LoggerLevelInfo
#define LOGGER_FORMAT_DEFAULT logger_format_default

typedef int (*logger_format)(FILE *file, LoggerLevel level, const char *source, int line, const char *message, ...);

/**
 * @brief Logger configuration.
 */
typedef struct
{
    /** @brief Logger level, below which log calls will be ignored. Defaults to `LoggerLevelInfo`. */
    LoggerLevel level;
    /** @brief Logger format function. */
    logger_format format;
    /** @brief Logger file handle. Defaults to `stderr`. */
    FILE *file;
} LoggerGlobal;

static LoggerGlobal logger_global = {.level = LOGGER_LEVEL_DEFAULT};

void logger_set_level(LoggerLevel level)
{
    logger_global.level = level;
}

void logger_set_format(logger_format format)
{
    logger_global.format = format;
}

void logger_set_file(FILE *file)
{
    logger_global.file = file;
}

#define LOGGER_FORMAT (logger_global.format ? logger_global.format : LOGGER_FORMAT_DEFAULT)
#define LOGGER_FILE (logger_global.file ? logger_global.file : LOGGER_FILE_DEFAULT)

#define log_expr(__level, ...) (logger_global.level <= __level && LOGGER_FORMAT(LOGGER_FILE, __level, "/"__FILE__, __LINE__, __VA_ARGS__))

#define log_error_expr(...) log_expr(LoggerLevelError, __VA_ARGS__)
#define log_warn_expr(...) log_expr(LoggerLevelWarn, __VA_ARGS__)
#define log_info_expr(...) log_expr(LoggerLevelInfo, __VA_ARGS__)
#define log_debug_expr(...) log_expr(LoggerLevelDebug, __VA_ARGS__)

#define log_error(...) (void)log_error_expr(__VA_ARGS__)
#define log_warn(...) (void)log_warn_expr(__VA_ARGS__)
#define log_info(...) (void)log_info_expr(__VA_ARGS__)
#define log_debug(...) (void)log_debug_expr(__VA_ARGS__)

#endif // CSYNTH_LOGGER_H
