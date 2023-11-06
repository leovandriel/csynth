//
// inv.h - Inverse function
//
// `inv(value)` returns 1 / value.
//
#ifndef COMPOSER_INV_H
#define COMPOSER_INV_H

#include <assert.h>
#include <math.h>

#include "../core/func.h"
#include "./cons.h"

static const double DIVISION_EPSILON = 1e-9;

double inv_eval(Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double value = gen_eval(args[0]);
    if (fabs(value) < DIVISION_EPSILON)
    {
        value = value >= 0 ? DIVISION_EPSILON : -DIVISION_EPSILON;
    }
    return 1.0 / value;
}

Func *inv(Func *value)
{
    return func_create(NULL, inv_eval, NULL, 0, NULL, 1, value);
}

#define div(a, b) mul(a, inv(b))

void test_inv()
{
    assert(gen_eval(gen_create(inv(cons(1)), .1)) == 1.0);
    assert(gen_eval(gen_create(inv(cons(-2)), .1)) == -0.5);
}

#endif // COMPOSER_INV_H
