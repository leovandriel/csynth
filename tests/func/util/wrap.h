#include "../../../src/func/gen/const.h"
#include "../../../src/func/util/wrap.h"
#include "../../util/test.h"

static double test_wrap_add(double input)
{
    assert_double_equal(input, 3);
    return input + 4;
}

void test_wrap()
{
    Func *fun = wrap(test_wrap_add, _(3));
    Gen *gen = gen_create(fun);
    Eval eval = eval_create(0.1);
    assert_double_equal(gen_eval(gen, eval), 7);
    gen_free(gen);
    func_free();
}
