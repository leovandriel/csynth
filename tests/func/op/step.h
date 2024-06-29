#include "../../../src/func/gen/timer.h"
#include "../../../src/func/op/step.h"
#include "../../util/test.h"

void test_step()
{
    Func *time = step_op(timer(), const_(0.5));
    Gen *gen = gen_create(time);
    Eval eval = {.step = {0.1, 0.1}};
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    gen_free(gen);
    func_free();
}
