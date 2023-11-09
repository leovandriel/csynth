//
// inv.h - Inverse function
//
// `inv(value)` returns 1 / value.
//
#ifndef CSYNTH_INV_H
#define CSYNTH_INV_H

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"

static double inv_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double value = gen_eval(args[0]);
    if (value < EPSILON && value > -EPSILON)
    {
        value = value >= 0 ? EPSILON : -EPSILON;
    }
    return 1.0 / value;
}

Func *inv(Func *value)
{
    return func_create(NULL, inv_eval, NULL, 0, NULL, 1, value);
}

void test_inv()
{
    assert_gen_equal(gen_create(inv(const_(1)), .1), 1.0);
    assert_gen_equal(gen_create(inv(const_(-2)), .1), -0.5);
}

#endif // CSYNTH_INV_H
