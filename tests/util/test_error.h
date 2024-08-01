#include "../../src/util/error.h"
#include "./test.h"

volatile static int test_error_count_global = 0;

int test_error_log(LoggerLevel level, __U const char *file, __U int line, const char *message, ...)
{
    va_list args = {0};
    va_start(args, message);
    assert_long_equal(level, LoggerLevelError);
    assert_string_equal(message, "unable to allocate memory");
    test_error_count_global++;
    va_end(args);
    return 0;
}

void test_error(void)
{
    logger_cb_global = test_error_log;
    assert_long_equal(test_error_count_global, 0);
    assert_long_equal(error_type_message(csErrorSome, "unable to allocate memory"), csErrorSome);
    assert_long_equal(test_error_count_global, 1);
    assert_null(error_null_message(csErrorSome, "unable to allocate memory"));
    assert_long_equal(test_error_count_global, 2);
    error_catch_message(csErrorSome, "unable to allocate memory");
    assert_long_equal(test_error_count_global, 3);
    assert_long_equal(error_type(csErrorMemoryAlloc), csErrorMemoryAlloc);
    assert_long_equal(test_error_count_global, 4);
    assert_null(error_null(csErrorMemoryAlloc));
    assert_long_equal(test_error_count_global, 5);
    error_catch(csErrorMemoryAlloc);
    assert_long_equal(test_error_count_global, 6);
}
