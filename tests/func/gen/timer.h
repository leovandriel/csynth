#include "../../../src/func/gen/timer.h"
#include "../../util/test.h"

void test_timer()
{
    Func *time = timer();
    Gen *gen = gen_create(time);
    Eval eval = {.step = {0.1, 0.1}};
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.1);
    assert_double_equal(gen_eval(gen, eval), 0.2);
    assert_double_equal(gen_eval(gen, eval), 0.3);
    assert_double_equal(gen_eval(gen, eval), 0.4);
    gen_free(gen);
    func_free();
}
