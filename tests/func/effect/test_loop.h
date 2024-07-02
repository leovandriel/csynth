#include "../../../src/func/effect/effects.h"
#include "../../../src/func/effect/loop.h"
#include "../../../src/func/op/ops.h"
#include "../../../src/func/time/times.h"
#include "../../util/test.h"

void test_loop()
{
    Func *time = loop(const_(0.5), step_op(const_(0.3), pitch_timer_(1)));
    Gen *gen = gen_create(time);
    EvalContext eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    gen_free(gen);
    func_free();
}
