#include "../../../src/func/gen/const.h"
#include "../../../src/func/util/wrap.h"
#include "../../util/test.h"

static double test_wrap_add(double input, double delta)
{
    assert_double_equal(input, 3);
    assert_double_equal(delta, 0.1);
    return input + 4;
}

void test_wrap()
{
    Func *fun = wrap(_(3), test_wrap_add);
    Gen *gen = gen_create(fun, 0.1);
    assert_gen_equal(gen, 7);
}