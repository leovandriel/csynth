#include "../../../src/func/gen/saw.h"
#include "../../../src/func/time/times.h"
#include "../../util/test.h"

void test_saw()
{
    Func *time = saw_create(pitch_ticker_(1));
    Gen *gen = gen_create(time);
    EvalContext eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, &eval), 0.0);
    assert_double_equal(gen_eval(gen, &eval), 0.2);
    assert_double_equal(gen_eval(gen, &eval), 0.4);
    assert_double_equal(gen_eval(gen, &eval), 0.6);
    assert_double_equal(gen_eval(gen, &eval), 0.8);
    assert_double_equal(gen_eval(gen, &eval), 1.0);
    assert_double_equal(gen_eval(gen, &eval), -0.8);
    assert_double_equal(gen_eval(gen, &eval), -0.6);
    assert_double_equal(gen_eval(gen, &eval), -0.4);
    assert_double_equal(gen_eval(gen, &eval), -0.2);
    assert_double_equal(gen_eval(gen, &eval), -0.0);
    gen_free(gen);
    func_free();
}
