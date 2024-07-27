#ifndef CSYNTH_MUL_H
#define CSYNTH_MUL_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double mul_eval(size_t count, Gen **args, Eval *eval, __U void *context)
{
    double output = 1.0;
    for (size_t i = 0; i < count; i++)
    {
        output *= gen_eval(args[i], eval);
    }
    return output;
}

/**
 * @brief Create a function of the product across all inputs.
 *
 * Can be used to add gain to a signal, e.g. to increase volume.
 *
 * @param count Number of arguments.
 * @param args Argument array.
 * @return Func* Multiplication function.
 */
Func *mul_create(size_t count, Func **args)
{
    return func_create_args(NULL, mul_eval, NULL, 0, NULL, FuncFlagNone, count, args, "arg");
}

#endif // CSYNTH_MUL_H
