#include "../../../src/func/gen/const.h"
#include "../../../src/func/gen/sine.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_sine_exact(void)
{
    Gen *gen = gen_create(sine_create(const_(0.1)));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852522924731);
    assert_double_equal(gen_eval(gen, NULL), 0.9510565162951535);
    assert_double_equal(gen_eval(gen, NULL), 0.9510565162951536);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852522924732);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000001);
    assert_double_equal(gen_eval(gen, NULL), -0.5877852522924730);
    assert_double_equal(gen_eval(gen, NULL), -0.9510565162951535);
    assert_double_equal(gen_eval(gen, NULL), -0.9510565162951536);
    assert_double_equal(gen_eval(gen, NULL), -0.5877852522924740);
    assert_double_equal(gen_eval(gen, NULL), -0.0000000000000011);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852522924724);
    gen_free(gen);
}

void test_sine_incremental(void)
{
    Gen *gen = gen_create(sine_create(sum_create(const_(.01))));
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0000000000000000);
    assert_double_equal(gen_eval(gen, NULL), 0.0627905195293134);
    assert_double_equal(gen_eval(gen, NULL), 0.1873813145857247);
    assert_double_equal(gen_eval(gen, NULL), 0.3681245526846780);
    assert_double_equal(gen_eval(gen, NULL), 0.5877852522924732);
    assert_double_equal(gen_eval(gen, NULL), 0.8090169943749475);
    assert_double_equal(gen_eval(gen, NULL), 0.9685831611286311);
    assert_double_equal(gen_eval(gen, NULL), 0.9822872507286886);
    assert_double_equal(gen_eval(gen, NULL), 0.7705132427757893);
    assert_double_equal(gen_eval(gen, NULL), 0.3090169943749471);
    assert_double_equal(gen_eval(gen, NULL), -0.3090169943749477);
    gen_free(gen);
}

void test_sine_range(void)
{
    for (size_t i = 0; i < 100; i++)
    {
        Gen *gen = gen_create(sine_create(const_(0.1)));
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