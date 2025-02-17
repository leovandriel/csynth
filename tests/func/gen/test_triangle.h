#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/triangle.h"
#include "../../util/test.h"

void test_triangle_exact(void)
{
    Gen *gen = gen_create(triangle_create(const_create(0.1), const_create(0)));
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.4);
    assert_double_equal(gen_eval(gen, NULL), 0.8);
    assert_double_equal(gen_eval(gen, NULL), 0.8);
    assert_double_equal(gen_eval(gen, NULL), 0.4);
    assert_double_equal(gen_eval(gen, NULL), -0.0);
    assert_double_equal(gen_eval(gen, NULL), -0.4);
    assert_double_equal(gen_eval(gen, NULL), -0.8);
    assert_double_equal(gen_eval(gen, NULL), -0.8);
    assert_double_equal(gen_eval(gen, NULL), -0.4);
    assert_double_equal(gen_eval(gen, NULL), 0.0);
    assert_double_equal(gen_eval(gen, NULL), 0.4);
    gen_free(gen);
}

void test_triangle_skew(void)
{
    Gen *gen = gen_create(triangle_create(const_create(0.1), const_create(-0.4)));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.6666666666666667);
    assert_double_equal(gen_eval(gen, NULL), 0.8571428571428571);
    assert_double_equal(gen_eval(gen, NULL), 0.5714285714285714);
    assert_double_equal(gen_eval(gen, NULL), 0.2857142857142856);
    assert_double_equal(gen_eval(gen, NULL), -0.0000000000000001);
    assert_double_equal(gen_eval(gen, NULL), -0.2857142857142858);
    assert_double_equal(gen_eval(gen, NULL), -0.5714285714285715);
    assert_double_equal(gen_eval(gen, NULL), -0.8571428571428572);
    assert_double_equal(gen_eval(gen, NULL), -0.6666666666666663);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000004);
    assert_double_equal(gen_eval(gen, NULL), 0.6666666666666672);
    gen_free(gen);
}

void test_triangle_range(void)
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(triangle_create(const_create(0.1), const_create(0)));
        assert_double_range(gen_eval(gen, NULL), -1.0, 1.0);
        gen_free(gen);
    }
}

void test_triangle(void)
{
    test_triangle_exact();
    test_triangle_range();
    test_triangle_skew();
    func_free();
}