#include "../../src/util/logger.h"
#include "./test.h"

typedef struct
{
    LoggerLevel level;
    const char *file;
    int line;
    const char *message;
    int arg;
} LoggerArgs;

static LoggerArgs test_logger_args_global = {0};

int test_logger_log(LoggerLevel level, const char *file, int line, const char *message, ...)
{
    va_list args = {0};
    va_start(args, message);
    test_logger_args_global = (LoggerArgs){
        .level = level,
        .file = file,
        .line = line,
        .message = message,
        .arg = va_arg(args, int),
    };
    va_end(args);
    return 0;
}

void test_logger(void)
{
    logger_cb_global = test_logger_log;
    log_info("test1", 1);
    assert_long_equal(test_logger_args_global.level, LoggerLevelInfo);
    assert_string_equal(strrchr(test_logger_args_global.file, '/'), "/test_logger.h");
    assert_long_equal(test_logger_args_global.line, 33);
    assert_string_equal(test_logger_args_global.message, "test1");
    assert_long_equal(test_logger_args_global.arg, 1);
    log_debug("test2", 2);
    assert_long_equal(test_logger_args_global.arg, 1);
}
