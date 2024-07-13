#include "../../../src/func/filter/adsr.h"
#include "../../../src/func/filter/envelopes.h"
#include "../../../src/func/util/time.h"
#include "../../util/test.h"

void test_adsr()
{
    Gen *gen = gen_create(adsr_op_(timer(EvalParamPitchTick), 0.01, 0.1, 0.7, 0.2, 1.2));
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.000);
    assert_double_equal(gen_eval(gen, &eval), 0.730);
    assert_double_equal(gen_eval(gen, &eval), 0.700);
    assert_double_equal(gen_eval(gen, &eval), 0.700);
    assert_double_equal(gen_eval(gen, &eval), 0.700);
    assert_double_equal(gen_eval(gen, &eval), 0.700);
    assert_double_equal(gen_eval(gen, &eval), 0.700);
    assert_double_equal(gen_eval(gen, &eval), 0.700);
    assert_double_equal(gen_eval(gen, &eval), 0.700);
    assert_double_equal(gen_eval(gen, &eval), 0.700);
    assert_double_equal(gen_eval(gen, &eval), 0.700);
    assert_double_equal(gen_eval(gen, &eval), 0.350);
    assert_double_equal(gen_eval(gen, &eval), 0.000);
    assert_double_equal(gen_eval(gen, &eval), 0.000);
    assert_double_equal(gen_eval(gen, &eval), 0.000);
    gen_free(gen);
    func_free();
}
