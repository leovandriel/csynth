#include "../../../src/func/effect/effects.h"
#include "../../../src/func/effect/loop.h"
#include "../../../src/func/op/ops.h"
#include "../../../src/func/util/time.h"
#include "../../util/test.h"

void test_loop()
{
    Gen *gen = gen_create(loop(const_(0.5), step_op(const_(0.3), timer(EvalParamPitchTick))));
    Eval eval = eval_create(0.1);
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
