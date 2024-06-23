#include "../../../src/func/gen/triangle.h"
#include "../../util/test.h"

void test_triangle()
{
    Func *time = triangle(const_(1));
    Gen *gen = gen_create(time);
    Eval eval = {.delta = 0.1};
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.4);
    assert_double_equal(gen_eval(gen, eval), 0.8);
    assert_double_equal(gen_eval(gen, eval), 0.8);
    assert_double_equal(gen_eval(gen, eval), 0.4);
    assert_double_equal(gen_eval(gen, eval), -0.0);
    assert_double_equal(gen_eval(gen, eval), -0.4);
    assert_double_equal(gen_eval(gen, eval), -0.8);
    assert_double_equal(gen_eval(gen, eval), -0.8);
    assert_double_equal(gen_eval(gen, eval), -0.4);
    assert_double_equal(gen_eval(gen, eval), 0.0);
    assert_double_equal(gen_eval(gen, eval), 0.4);
    gen_free(gen);
    func_free();
}
