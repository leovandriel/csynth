#ifndef COMPOSER_MIN_H
#define COMPOSER_MIN_H

#include <float.h>
#include <stdarg.h>

#include "../core/func.h"

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

#endif // COMPOSER_MIN_H
