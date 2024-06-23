#include "../../../src/func/filter/limit.h"
#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_limit()
{
    Func *time = limit(square_osc(), const_(3));
    Gen *gen = gen_create(time);
    Eval eval = {.audio_step = 0.1};
    assert_double_equal(gen_eval(gen, eval), 0.30);
    assert_double_equal(gen_eval(gen, eval), 0.60);
    assert_double_equal(gen_eval(gen, eval), 0.90);
    assert_double_equal(gen_eval(gen, eval), 1.00);
    assert_double_equal(gen_eval(gen, eval), 1.00);
    assert_double_equal(gen_eval(gen, eval), 0.70);
    assert_double_equal(gen_eval(gen, eval), 0.40);
    assert_double_equal(gen_eval(gen, eval), 0.10);
    assert_double_equal(gen_eval(gen, eval), -0.20);
    assert_double_equal(gen_eval(gen, eval), -0.50);
    assert_double_equal(gen_eval(gen, eval), -0.20);
    assert_double_equal(gen_eval(gen, eval), 0.10);
    gen_free(gen);
    func_free();
}
