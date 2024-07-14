//
// inv.h - Inverse function
//
// `inv(value)` returns 1 / value.
//
#ifndef CSYNTH_INV_H
#define CSYNTH_INV_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double inv_eval(__U size_t count, Gen **args, Eval *eval, __U void *context)
{
    double input = gen_eval(args[0], eval);
    if (input < FUNC_EPSILON && input > -FUNC_EPSILON)
    {
        input = input >= 0 ? FUNC_EPSILON : -FUNC_EPSILON;
    }
    return 1.0 / input;
}

Func *inv_create(Func *input)
{
    return func_create(NULL, inv_eval, NULL, 0, NULL, FuncFlagNone, ARGS(input));
}

#endif // CSYNTH_INV_H
