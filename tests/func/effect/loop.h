#include "../../../src/func/effect/loop.h"
#include "../../../src/func/gen/timer.h"
#include "../../../src/func/op/step.h"
#include "../../util/test.h"

void test_loop()
{
    Func *time = loop(step_op(timer(), const_(0.3)), const_(0.5));
    Gen *gen = gen_create(time);
    Eval eval = {.audio_step = 0.1, .control_step = 0.1};
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    gen_free(gen);
    func_free();
}
