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

/**
 * @brief Create a function for the inverse of the input, i.e. 1 / input.
 *
 * Inputs that are close to zero are clamped to `FUNC_EPSILON` to avoid division
 * by zero.
 *
 * @param input Input value.
 * @return Func* Function object.
 */
Func *inv_create(Func *input)
{
    return func_create(NULL, inv_eval, NULL, 0, NULL, FuncFlagNone, input);
}

#endif // CSYNTH_INV_H
