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
#include "../gen/const.h"

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

Func *max_args(int count, ...)
{
    va_list valist = {0};
    va_start(valist, count);
    Func *output = func_create_va(NULL, max_eval, NULL, 0, NULL, FuncFlagNone, count, valist);
    va_end(valist);
    return output;
}

#define max(...) (max_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *max_(Func *input, double min)
{
    return max(input, const_(min));
}

Func *max_array(int count, Func **args)
{
    return func_create_array(NULL, max_eval, NULL, 0, NULL, FuncFlagNone, count, args);
}

#endif // CSYNTH_MAX_H
