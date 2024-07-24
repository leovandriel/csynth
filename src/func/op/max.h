#ifndef CSYNTH_MAX_H
#define CSYNTH_MAX_H

#include <float.h>

#include "../../core/func.h"
#include "../../core/gen.h"

static double max_eval(size_t count, Gen **args, Eval *eval, __U void *context)
{
    double max = -FLT_MAX;
    for (size_t i = 0; i < count; i++)
    {
        double input = gen_eval(args[i], eval);
        if (max < input)
        {
            max = input;
        }
    }
    return max;
}

/**
 * @brief Create a function for the maximum across all inputs.
 *
 * Can be used to clamp a signal to a maximum value, e.g. to prevent clipping or
 * create a distortion effect.
 *
 * @param count Number of arguments.
 * @param args Argument array.
 * @return Func* Function object.
 */
Func *max_create(size_t count, Func **args)
{
    return func_create_args(NULL, max_eval, NULL, 0, NULL, FuncFlagNone, count, args, "arg");
}

#endif // CSYNTH_MAX_H
