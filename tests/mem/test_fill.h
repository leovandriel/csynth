#include "../../src/mem/fill.h"
#include "../util/test.h"

void test_fill(void)
{
    rand_seed(0);
    for (size_t i = 0; i < 100; i++)
    {
        assert_double_range(fill_rand_0_1(0), 0, 1);
        assert_double_range(fill_rand_1_1(0), -1, 1);
        assert_double_equal(fill_inc(i), i);
    }
}
