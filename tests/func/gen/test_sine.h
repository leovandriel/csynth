#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/sine.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_sine_exact(void)
{
    Gen *gen = gen_create(sine_create(const_create(0.1)));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852246243184);
    assert_double_equal(gen_eval(gen, NULL), 0.9510564491561904);
    assert_double_equal(gen_eval(gen, NULL), 0.9510564491561903);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852246243183);
    assert_double_equal(gen_eval(gen, NULL), -0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), -0.5877852246243183);
    assert_double_equal(gen_eval(gen, NULL), -0.9510564491561903);
    assert_double_equal(gen_eval(gen, NULL), -0.9510564491561905);
    assert_double_equal(gen_eval(gen, NULL), -0.5877852246243188);
    assert_double_equal(gen_eval(gen, NULL), -0.0000000000000007);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852246243177);
    gen_free(gen);
}

void test_sine_incremental(void)
{
    Gen *gen = gen_create(sine_create(sum_create(const_create(.01))));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0627905181746333);
    assert_double_equal(gen_eval(gen, NULL), 0.1873813045396087);
    assert_double_equal(gen_eval(gen, NULL), 0.3681245256589130);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852246243184);
    assert_double_equal(gen_eval(gen, NULL), 0.8090169563052816);
    assert_double_equal(gen_eval(gen, NULL), 0.9685830991337381);
    assert_double_equal(gen_eval(gen, NULL), 0.9822871980270402);
    assert_double_equal(gen_eval(gen, NULL), 0.7705132188468167);
    assert_double_equal(gen_eval(gen, NULL), 0.3090169725639709);
    assert_double_equal(gen_eval(gen, NULL), -0.3090169725639715);
    gen_free(gen);
}

void test_sine_range(void)
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(sine_create(const_create(0.1)));
        assert_double_range(gen_eval(gen, NULL), -1.0, 1.0);
        gen_free(gen);
    }
}

void test_sine(void)
{
    test_sine_exact();
    test_sine_incremental();
    test_sine_range();
    func_free();
}