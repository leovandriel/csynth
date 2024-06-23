#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_square()
{
    Func *time = square_osc();
    Gen *gen = gen_create(time);
    Eval eval = {.audio_step = 0.1, .control_step = 0.1};
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), -1.0);
    assert_double_equal(gen_eval(gen, eval), -1.0);
    assert_double_equal(gen_eval(gen, eval), -1.0);
    assert_double_equal(gen_eval(gen, eval), -1.0);
    assert_double_equal(gen_eval(gen, eval), -1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    assert_double_equal(gen_eval(gen, eval), 1.0);
    gen_free(gen);
    func_free();
}
