#include "../../../src/func/gen/square.h"
#include "../../../src/func/time/times.h"
#include "../../util/test.h"

void test_square()
{
    Func *time = square_create(pitch_ticker_(1));
    Gen *gen = gen_create(time);
    EvalContext eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), -1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    gen_free(gen);
    func_free();
}
