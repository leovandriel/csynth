#include "../../../src/func/gen/const.h"
#include "../../../src/func/util/wrap.h"
#include "../../util/test.h"

static double test_wrap_add(double input, double delta, void *context)
{
    assert_double_equal(input, 3);
    assert_double_equal(delta, 0.1);
    assert_long_equal(*(int *)context, 2);
    return input + 4;
}

void test_wrap()
{
    int context = 2;
    Func *fun = wrap_filter(_(3), test_wrap_add, &context);
    Gen *gen = gen_create(fun, 0.1);
    assert_gen_equal(gen, 7);
}
