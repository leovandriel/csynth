//
// min.h - Min function
//
// `min(...)` returns the minimum of the input functions.
//
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

Func *min_create(size_t count, Func **args)
{
    return func_create(NULL, min_eval, NULL, 0, NULL, FuncFlagNone, count, args);
}

#endif // CSYNTH_MIN_H
