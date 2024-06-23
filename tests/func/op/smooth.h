#include "../../../src/func/gen/timer.h"
#include "../../../src/func/op/smooth.h"
#include "../../util/test.h"

void test_smooth()
{
    Func *time = smooth_op(timer(), const_(0.3), const_(0.7));
    Gen *gen = gen_create(time);
    Eval eval = {.delta = 0.1};
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
