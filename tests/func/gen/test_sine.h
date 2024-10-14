#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/sine.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_sine_exact(void)
{
    Gen *gen = gen_create(sine_create(const_create(0.1)));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852522924731);
    assert_double_equal(gen_eval(gen, NULL), 0.9510565162951536);
    assert_double_equal(gen_eval(gen, NULL), 0.9510565162951538);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852522924734);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000002);
    assert_double_equal(gen_eval(gen, NULL), -0.5877852522924730);
    assert_double_equal(gen_eval(gen, NULL), -0.9510565162951536);
    assert_double_equal(gen_eval(gen, NULL), -0.9510565162951539);
    assert_double_equal(gen_eval(gen, NULL), -0.5877852522924736);
    assert_double_equal(gen_eval(gen, NULL), -0.0000000000000005);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852522924728);
    gen_free(gen);
}

void test_sine_incremental(void)
{
    Gen *gen = gen_create(sine_create(sum_create(const_create(.01))));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0627905195293134);
    assert_double_equal(gen_eval(gen, NULL), 0.1873813145857246);
    assert_double_equal(gen_eval(gen, NULL), 0.3681245526846779);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852522924731);
    assert_double_equal(gen_eval(gen, NULL), 0.8090169943749473);
    assert_double_equal(gen_eval(gen, NULL), 0.9685831611286311);
    assert_double_equal(gen_eval(gen, NULL), 0.9822872507286887);
    assert_double_equal(gen_eval(gen, NULL), 0.7705132427757889);
    assert_double_equal(gen_eval(gen, NULL), 0.3090169943749470);
    assert_double_equal(gen_eval(gen, NULL), -0.3090169943749478);
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