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

static double min_eval(int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double min = FLT_MAX;
    for (int i = 0; i < count; i++)
    {
        double f = gen_eval(args[i]);
        if (min > f)
        {
            min = f;
        }
    }
    return min;
}

Func *min_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, min_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, count, valist);
    va_end(valist);
    return func;
}

#define min(...) (min_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *min_(Func *input, double max)
{
    return min(input, const_(max));
}

Func *min_array(int count, Func **args)
{
    return func_create_array(NULL, min_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, count, args);
}

#endif // CSYNTH_MIN_H
