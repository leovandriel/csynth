#include "../../src/mem/fill.h"
#include "../util/test.h"

void test_fill(void)
{
    Random random = random_create(0);
    for (size_t i = 0; i < 100; i++)
    {
        assert_double_range(fill_rand_0_1(0, &random), 0, 1);
        assert_double_range(fill_rand_1_1(0, &random), -1, 1);
        assert_double_equal(fill_inc(i, NULL), i);
    }
}
