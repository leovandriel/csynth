#ifndef COMPOSER_MAX_H
#define COMPOSER_MAX_H

#include <float.h>
#include <stdarg.h>

#include "../core/func.h"

double max_eval(Func **args, int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double max = -FLT_MAX;
    for (int i = 0; i < count; i++)
    {
        double f = func_eval(args[i]);
        if (max < f)
        {
            max = f;
        }
    }
    return max;
}

Func *max_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, max_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

#define max(...) max_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__)

#endif // COMPOSER_MAX_H
