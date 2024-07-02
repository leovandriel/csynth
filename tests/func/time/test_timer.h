#include "../../../src/func/time/times.h"
#include "../../util/test.h"

void test_timer()
{
    Func *time = pitch_timer_(1);
    Gen *gen = gen_create(time);
    EvalContext eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.2);
    assert_double_equal(gen_eval(gen, &eval), 0.3);
    assert_double_equal(gen_eval(gen, &eval), 0.4);
    gen_free(gen);
    func_free();
}
