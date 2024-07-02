#include "../../../src/func/effect/continuous.h"
#include "../../../src/func/effect/effects.h"
#include "../../../src/func/filter/envelopes.h"
#include "../../util/test.h"

void test_continuous()
{
    Func *time = loop_(2, continuous_create(linear_env_(1, 0, 1)));
    Gen *gen = gen_create(time);
    EvalContext eval = eval_create(1.0);
    assert_double_equal(gen_eval(gen, &eval), 0);
    assert_double_equal(gen_eval(gen, &eval), 1);
    assert_double_equal(gen_eval(gen, &eval), 2);
    assert_double_equal(gen_eval(gen, &eval), 3);
    assert_double_equal(gen_eval(gen, &eval), 4);
    gen_free(gen);
    func_free();
}
