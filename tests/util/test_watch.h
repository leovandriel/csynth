#include "../../src/util/watch.h"
#include "./test.h"

void test_watch(void)
{
    Watch watch = {0};
    assert_long_equal(watch_init(&watch, "README.md"), 0);
    watch_close(&watch);
}