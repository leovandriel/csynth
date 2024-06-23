#include "../../../src/func/effect/delay.h"
#include "../../util/test.h"

void test_delay()
{
    Func *time = delay(const_(1), const_(0.5));
    Gen *gen = gen_create(time);
    Eval eval = {.delta = 0.1};
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
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    gen_free(gen);
    func_free();
}
