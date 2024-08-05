#include "../../src/util/logger.h"
#include "./test.h"

typedef struct
{
    FILE *file;
    LoggerLevel level;
    const char *source;
    int line;
    const char *message;
    int arg;
} LoggerArgs;

static LoggerArgs test_logger_args_global = {0};

int test_logger_log(FILE *file, LoggerLevel level, const char *source, int line, const char *message, ...)
{
    va_list args = {0};
    va_start(args, message);
    test_logger_args_global = (LoggerArgs){
        .file = file,
        .level = level,
        .source = source,
        .line = line,
        .message = message,
        .arg = va_arg(args, int),
    };
    va_end(args);
    return 0;
}

void test_logger_format(void)
{
    logger_set_format(test_logger_log);
    log_info("test1", 1);
    assert_long_equal(test_logger_args_global.level, LoggerLevelInfo);
    assert_string_equal(strrchr(test_logger_args_global.source, '/'), "/test_logger.h");
    assert_long_equal(test_logger_args_global.line, 35);
    assert_string_equal(test_logger_args_global.message, "test1");
    assert_long_equal(test_logger_args_global.arg, 1);
    log_debug("test2", 2);
    assert_long_equal(test_logger_args_global.arg, 1);
    logger_set_format(NULL);
}

void test_logger_file(void)
{
    char buffer[1024] = {0};
    FILE *file = fmemopen(buffer, sizeof(buffer), "w");
    assert_not_null(file);
    logger_set_file(file);
    log_info("test1");
    assert_long_equal(fclose(file), 0);
    assert_string_equal(buffer + 30, " INFO test_logger.h:52 - test1\n");
    logger_set_file(NULL);
}

void test_logger(void)
{
    test_logger_format();
    test_logger_file();
}