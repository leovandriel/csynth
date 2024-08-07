#include "../../../src/func/filter/adsr.h"
#include "../../../src/func/gen/const.h"
#include "../../../src/func/op/sum.h"
#include "../../util/test.h"

void test_adsr(void)
{
    Gen *gen = gen_create(adsr_create(sum_create(const_create(0.1)), const_create(0.01), const_create(0.1), const_create(0.7), const_create(0.2), const_create(1.2)));
    assert_double_equal(gen_eval(gen, NULL), 0.000);
    assert_double_equal(gen_eval(gen, NULL), 0.730);
    assert_double_equal(gen_eval(gen, NULL), 0.700);
    assert_double_equal(gen_eval(gen, NULL), 0.700);
    assert_double_equal(gen_eval(gen, NULL), 0.700);
    assert_double_equal(gen_eval(gen, NULL), 0.700);
    assert_double_equal(gen_eval(gen, NULL), 0.700);
    assert_double_equal(gen_eval(gen, NULL), 0.700);
    assert_double_equal(gen_eval(gen, NULL), 0.700);
    assert_double_equal(gen_eval(gen, NULL), 0.700);
    assert_double_equal(gen_eval(gen, NULL), 0.700);
    assert_double_equal(gen_eval(gen, NULL), 0.350);
    assert_double_equal(gen_eval(gen, NULL), 0.000);
    assert_double_equal(gen_eval(gen, NULL), 0.000);
    assert_double_equal(gen_eval(gen, NULL), 0.000);
    gen_free(gen);
    func_free();
}
