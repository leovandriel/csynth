//
// min.h - Min function
//
// `min(...)` returns the minimum of the input functions.
// - clamp(value, min, max) - Ensure value is clipped to [min, max]
// - clamp_ - Take double arguments instead of functions
//
#ifndef COMPOSER_MIN_H
#define COMPOSER_MIN_H

#include <assert.h>
#include <float.h>
#include <stdarg.h>

#include "../core/func.h"
#include "./cons.h"
#include "./max.h"

double min_eval(Gen **args, int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
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

#define min(...) min_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__)
#define clamp(_value, _min, _max) min(max(_value, _min), _max)
#define clamp_(_value, _min, _max) clamp(_value, cons(_min), cons(_max))

void test_min()
{
    assert(gen_eval(gen_create(min(cons(1), cons(2)), .1)) == 1.0);
    assert(gen_eval(gen_create(min(cons(2), cons(1)), .1)) == 1.0);
    assert(gen_eval(gen_create(min(cons(4), cons(2), cons(3)), .1)) == 2.0);
    assert(gen_eval(gen_create(min(cons(1)), .1)) == 1.0);
}

#endif // COMPOSER_MIN_H
