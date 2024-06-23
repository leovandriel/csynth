#include "../../../src/func/effect/continuous.h"
#include "../../../src/func/effect/loop.h"
#include "../../../src/func/filter/envelopes.h"
#include "../../util/test.h"

void test_continuous()
{
    Func *time = loop_(continuous(linear_env_(0, 1, 1)), 2);
    Gen *gen = gen_create(time);
    Eval eval = {.delta = 1};
    assert_double_equal(gen_eval(gen, eval), 0);
    assert_double_equal(gen_eval(gen, eval), 1);
    assert_double_equal(gen_eval(gen, eval), 2);
    assert_double_equal(gen_eval(gen, eval), 3);
    assert_double_equal(gen_eval(gen, eval), 4);
    gen_free(gen);
    func_free();
}
