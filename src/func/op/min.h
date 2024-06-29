//
// min.h - Min function
//
// `min(...)` returns the minimum of the input functions.
//
#ifndef CSYNTH_MIN_H
#define CSYNTH_MIN_H

#include <float.h>
#include <stdarg.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double min_eval(int count, Gen **args, Eval eval, __U void *context)
{
    double min = FLT_MAX;
    for (int i = 0; i < count; i++)
    {
        double input = gen_eval(args[i], eval);
        if (min > input)
        {
            min = input;
        }
    }
    return min;
}

Func *min_array(int count, Func **args)
{
    return func_create_array(NULL, min_eval, NULL, 0, NULL, FuncFlagNone, count, args);
}

#define min(...) (min_array(FUNCS(__VA_ARGS__)))

Func *min_(Func *input, double max)
{
    return min(input, const_(max));
}

#endif // CSYNTH_MIN_H
