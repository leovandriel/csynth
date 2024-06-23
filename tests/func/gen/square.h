#include "../../../src/func/gen/square.h"
#include "../../util/test.h"

void test_square()
{
    Func *time = square(const_(1));
    Gen *gen = gen_create(time);
    Eval eval = {.delta = 0.1};
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
