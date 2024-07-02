#include "../../../src/func/op/ops.h"
#include "../../../src/func/op/smooth.h"
#include "../../../src/func/time/times.h"
#include "../../util/test.h"

void test_smooth()
{
    Func *time = smooth_op(const_(0.3), const_(0.7), pitch_timer_(1));
    Gen *gen = gen_create(time);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, eval), 0.000000);
    assert_double_equal(gen_eval(gen, eval), 0.000000);
    assert_double_equal(gen_eval(gen, eval), 0.000000);
    assert_double_equal(gen_eval(gen, eval), 0.000000);
    assert_double_equal(gen_eval(gen, eval), 0.156250);
    assert_double_equal(gen_eval(gen, eval), 0.500000);
    assert_double_equal(gen_eval(gen, eval), 0.843750);
    assert_double_equal(gen_eval(gen, eval), 1.000000);
    assert_double_equal(gen_eval(gen, eval), 1.000000);
    assert_double_equal(gen_eval(gen, eval), 1.000000);
    gen_free(gen);
    func_free();
}
