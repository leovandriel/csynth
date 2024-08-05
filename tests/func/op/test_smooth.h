#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/smooth.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_smooth_up(void)
{
    Gen *gen = gen_create(smooth_create(const_create(0.3), const_create(0.7), sum_create(const_create(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.156250);
    assert_double_equal(gen_eval(gen, NULL), 0.500000);
    assert_double_equal(gen_eval(gen, NULL), 0.843750);
    assert_double_equal(gen_eval(gen, NULL), 1.000000);
    assert_double_equal(gen_eval(gen, NULL), 1.000000);
    assert_double_equal(gen_eval(gen, NULL), 1.000000);
    gen_free(gen);
}

void test_smooth_down(void)
{
    Gen *gen = gen_create(smooth_create(const_create(0.7), const_create(0.3), sum_create(const_create(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 1.000000);
    assert_double_equal(gen_eval(gen, NULL), 1.000000);
    assert_double_equal(gen_eval(gen, NULL), 1.000000);
    assert_double_equal(gen_eval(gen, NULL), 1.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.843750);
    assert_double_equal(gen_eval(gen, NULL), 0.500000);
    assert_double_equal(gen_eval(gen, NULL), 0.156250);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    gen_free(gen);
}

void test_smooth_same(void)
{
    Gen *gen = gen_create(smooth_create(const_create(0.5), const_create(0.5), sum_create(const_create(0.1))));
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 0.000000);
    assert_double_equal(gen_eval(gen, NULL), 1.000000);
    assert_double_equal(gen_eval(gen, NULL), 1.000000);
    gen_free(gen);
}

void test_smooth(void)
{
    test_smooth_up();
    test_smooth_down();
    test_smooth_same();
    func_free();
}