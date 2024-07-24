#ifndef CSYNTH_MIN_H
#define CSYNTH_MIN_H

#include <float.h>

#include "../../core/func.h"
#include "../../core/gen.h"

static double min_eval(size_t count, Gen **args, Eval *eval, __U void *context)
{
    double min = FLT_MAX;
    for (size_t i = 0; i < count; i++)
    {
        double input = gen_eval(args[i], eval);
        if (min > input)
        {
            min = input;
        }
    }
    return min;
}

/**
 * @brief Create a function for minimum across all inputs.
 *
 * Can be used to clamp a signal to a minimum value, e.g. to prevent clipping or
 * create a distortion effect.
 *
 * @param count Number of arguments.
 * @param args Argument array.
 * @return Func* Function object.
 */
Func *min_create(size_t count, Func **args)
{
    return func_create_args(NULL, min_eval, NULL, 0, NULL, FuncFlagNone, count, args, "arg");
}

#endif // CSYNTH_MIN_H
