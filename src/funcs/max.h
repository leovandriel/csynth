#ifndef COMPOSER_MAX_H
#define COMPOSER_MAX_H

#include <stdarg.h>
#include <float.h>

#include "../core/func.h"

double max_eval(unsigned long index, double rate, Func **args, int count, __attribute__((unused)) void *context)
{
    double max = -FLT_MAX;
    for (int i = 0; i < count; i++)
    {
        double f = func_eval(args[i], index, rate);
        if (max < f)
        {
            max = f;
        }
    }
    return max;
}

Func *max_n(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, max_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

Func *max(Func *a, Func *b)
{
    return max_n(2, a, b);
}

Func *max_3(Func *a, Func *b, Func *c)
{
    return max_n(3, a, b, c);
}

Func *max_4(Func *a, Func *b, Func *c, Func *d)
{
    return max_n(4, a, b, c, d);
}

#endif // COMPOSER_MAX_H
