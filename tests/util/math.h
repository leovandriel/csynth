#include "../../src/util/math.h"
#include "./test.h"

void test_sin()
{
    for (double x = -2; x < 2; x += .1)
    {
        double phase = x * PI_M_2;
        assert_double_range(sin_lookup(phase), sin(phase) + -1e-7, sin(phase) + 1e-7);
    }
}

void test_math()
{
    test_sin();
}
