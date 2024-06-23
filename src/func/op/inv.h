//
// inv.h - Inverse function
//
// `inv(value)` returns 1 / value.
//
#ifndef CSYNTH_INV_H
#define CSYNTH_INV_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double inv_eval(__U int count, Gen **args, __U double delta, __U void *context)
{
    double value = gen_eval(args[0]);
    if (value < FUNC_EPSILON && value > -FUNC_EPSILON)
    {
        value = value >= 0 ? FUNC_EPSILON : -FUNC_EPSILON;
    }
    return 1.0 / value;
}

Func *inv(Func *value)
{
    return func_create(NULL, inv_eval, NULL, 0, NULL, FuncFlagNone, 1, value);
}

#endif // CSYNTH_INV_H
