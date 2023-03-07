#ifndef COMPOSER_MIN_H
#define COMPOSER_MIN_H

#include <stdarg.h>
#include <float.h>

#include "../core/func.h"

double min_eval(unsigned long index, double rate, Func **args, int count, __attribute__((unused)) void *context)
{
    double min = FLT_MAX;
    for (int i = 0; i < count; i++)
    {
        double f = func_eval(args[i], index, rate);
        if (min > f)
        {
            min = f;
        }
    }
    return min;
}

Func *min_n(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, min_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

Func *min(Func *a, Func *b)
{
    return min_n(2, a, b);
}

Func *min_3(Func *a, Func *b, Func *c)
{
    return min_n(3, a, b, c);
}

Func *min_4(Func *a, Func *b, Func *c, Func *d)
{
    return min_n(4, a, b, c, d);
}

#endif // COMPOSER_MIN_H
