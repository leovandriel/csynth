#include "../../src/util/time.h"
#include "./test.h"

void test_time(void)
{
    double start = time_sec();
    assert_double_range(time_sec() - start, 0.0, 0.1);
    time_sleep(0.1);
}