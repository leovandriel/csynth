//
// max.h - Max function
//
// `max(...)` returns the maximum of the input functions.
//
#ifndef CSYNTH_MAX_H
#define CSYNTH_MAX_H

#include <float.h>
#include <stdarg.h>

#include "../../core/func.h"
#include "../../core/gen.h"

static double max_eval(int count, Gen **args, Eval eval, __U void *context)
{
    double max = -FLT_MAX;
    for (int i = 0; i < count; i++)
    {
        double input = gen_eval(args[i], eval);
        if (max < input)
        {
            max = input;
        }
    }
    return max;
}

Func *max_create(int count, Func **args)
{
    return func_create(NULL, max_eval, NULL, 0, NULL, FuncFlagNone, count, args);
}

#endif // CSYNTH_MAX_H
