#include "../../src/util/math.h"
#include "./test.h"

void test_sin()
{
    for (int x = -20; x < 20; x += 1)
    {
        double phase = x * 0.1 * PI_M_2;
        assert_double_range(sin_lookup(phase), sin(phase) + -1e-7, sin(phase) + 1e-7);
    }
}

void test_math()
{
    test_sin();
}
