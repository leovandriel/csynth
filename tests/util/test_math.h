#include "../../src/util/math.h"
#include "./test.h"

void test_fast_pow(void)
{
    assert_double_equal(fast_pow(0.0, 0), 1.0);
    assert_double_equal(fast_pow(1.0, 0), 1.0);
    assert_double_equal(fast_pow(0.0, 1), 0.0);
    assert_double_equal(fast_pow(1.0, 1), 1.0);
    assert_double_equal(fast_pow(0.0, 2), 0.0);
    assert_double_equal(fast_pow(1.0, 2), 1.0);
    assert_double_equal(fast_pow(0.5, 0), 1.0);
    assert_double_equal(fast_pow(0.5, 1), 0.5);
    assert_double_equal(fast_pow(0.5, 2), 0.25);
    assert_double_equal(fast_pow(0.5, 3), 0.125);
    assert_double_equal(fast_pow(0.5, 4), 0.0625);
    assert_double_equal(fast_pow(0.5, 6), 0.015625);
}

void test_fast_sqrt_0to1(void)
{
    assert_double_equal(fast_sqrt_0to1(0.0) - sqrt(0.0), 0.0);
    assert_double_equal(fast_sqrt_0to1(1.0) - sqrt(1.0), 0.0);
    assert_double_equal(fast_sqrt_0to1(0.25) - sqrt(0.25), 0.0);
    assert_double_equal(fast_sqrt_0to1(0.5) - sqrt(0.5), -0.0147990888788553);
    assert_double_equal(fast_sqrt_0to1(0.75) - sqrt(0.75), -0.0121792499382847);
}

void test_math(void)
{
    test_fast_pow();
    test_fast_sqrt_0to1();
}