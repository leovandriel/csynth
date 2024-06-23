#include "../../../src/func/gen/timer.h"
#include "../../../src/func/op/adsr.h"
#include "../../util/test.h"

void test_adsr()
{
    Func *time = adsr_op_(timer(), 0.01, 0.1, 0.7, 0.2, 1.2);
    Gen *gen = gen_create(time);
    Eval eval = {.audio_step = 0.1};
    assert_double_equal(gen_eval(gen, eval), 0.000);
    assert_double_equal(gen_eval(gen, eval), 0.730);
    assert_double_equal(gen_eval(gen, eval), 0.700);
    assert_double_equal(gen_eval(gen, eval), 0.700);
    assert_double_equal(gen_eval(gen, eval), 0.700);
    assert_double_equal(gen_eval(gen, eval), 0.700);
    assert_double_equal(gen_eval(gen, eval), 0.700);
    assert_double_equal(gen_eval(gen, eval), 0.700);
    assert_double_equal(gen_eval(gen, eval), 0.700);
    assert_double_equal(gen_eval(gen, eval), 0.700);
    assert_double_equal(gen_eval(gen, eval), 0.700);
    assert_double_equal(gen_eval(gen, eval), 0.350);
    assert_double_equal(gen_eval(gen, eval), 0.000);
    assert_double_equal(gen_eval(gen, eval), 0.000);
    assert_double_equal(gen_eval(gen, eval), 0.000);
    gen_free(gen);
    func_free();
}
