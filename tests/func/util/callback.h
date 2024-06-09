#include "../../../src/func/gen/const.h"
#include "../../../src/func/util/callback.h"
#include "../../util/test.h"

static double test_callback_add(int count, Gen **args, double delta, void *context)
{
    assert_long_equal(count, 2);
    assert_double_equal(delta, 0.1);
    assert_long_equal(*(int *)context, 2);
    return gen_eval(args[0]) + gen_eval(args[1]);
}

void test_callback()
{
    int context = 2;
    Func *fun = callback_func(test_callback_add, &context, const_(3), const_(4));
    Gen *gen = gen_create(fun, 0.1);
    assert_gen_equal(gen, 7);
}
