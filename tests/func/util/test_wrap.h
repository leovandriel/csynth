#include "../../../src/func/gen/const.h"
#include "../../../src/func/util/wrap.h"
#include "../../util/test.h"

static double test_wrap_add(double input, __U void *context)
{
    assert_double_equal(input, 3);
    return input + 4;
}

void test_wrap()
{
    Func *fun = wrap_create(test_wrap_add, _(3), NULL);
    Gen *gen = gen_create(fun);
    assert_double_equal(gen_eval(gen, NULL), 7);
    gen_free(gen);
    func_free();
}
