//
// inv.h - Inverse function
//
// `inv(value)` returns 1 / value.
//
#ifndef CSYNTH_INV_H
#define CSYNTH_INV_H

#include <assert.h>
#include <math.h>

#include "../../core/func.h"
#include "../gen/const.h"
#include "../op/mul.h"
#include "../op/add.h"
#include "../op/neg.h"

static const double INV_EPSILON = 1e-9;

static double inv_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double value = gen_eval(args[0]);
    if (fabs(value) < INV_EPSILON)
    {
        value = value >= 0 ? INV_EPSILON : -INV_EPSILON;
    }
    return 1.0 / value;
}

Func *inv(Func *value)
{
    return func_create(NULL, inv_eval, NULL, 0, NULL, 1, value);
}

Func *dvd(Func *a, Func *b) { return mul(a, inv(b)); }
Func *dvd_(Func *a, double b) { return dvd(a, const_(b)); }

Func *kr(Func *f) { return dvd_(add_(f, 1), 2); }
Func *kr_range(Func *f, Func *min, Func *max) { return add(mul(kr(f), sub(max, min)), min); }
Func *kr_range_(Func *f, double min, double max) { return add(mul(kr(f), sub(const_(max), const_(min))), const_(min)); }

void test_inv()
{
    assert(gen_eval(gen_create(inv(const_(1)), .1)) == 1.0);
    assert(gen_eval(gen_create(inv(const_(-2)), .1)) == -0.5);
}

#endif // CSYNTH_INV_H
