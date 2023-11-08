//
// min.h - Min function
//
// `min(...)` returns the minimum of the input functions.
// - clamp(value, min, max) - Ensure value is clipped to [min, max]
// - clamp_ - Take double arguments instead of functions
//
#ifndef CSYNTH_MIN_H
#define CSYNTH_MIN_H

#include <assert.h>
#include <float.h>
#include <stdarg.h>

#include "../../core/func.h"
#include "../gen/const.h"
#include "./max.h"

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
    Func *func = func_create_va(NULL, min_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

#define min(...) (min_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__))

Func *min_(Func *input, double max)
{
    return min(input, const_(max));
}
Func *clamp(Func *value, Func *min, Func *max) { return min(max(value, min), max); }
Func *clamp_(Func *value, double min, double max) { return clamp(value, const_(min), const_(max)); }

Func *min_array(int count, Func **args)
{
    return func_create_array(NULL, min_eval, NULL, 0, NULL, count, args);
}

void test_min()
{
    assert(gen_eval(gen_create(min(const_(1), const_(2)), .1)) == 1.0);
    assert(gen_eval(gen_create(min(const_(2), const_(1)), .1)) == 1.0);
    assert(gen_eval(gen_create(min(const_(4), const_(2), const_(3)), .1)) == 2.0);
    assert(gen_eval(gen_create(min(const_(1)), .1)) == 1.0);
}

#endif // CSYNTH_MIN_H
