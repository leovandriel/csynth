#ifndef COMPOSER_SUM_H
#define COMPOSER_SUM_H

#include <stdarg.h>

#include "../core/func.h"

double sum_eval(unsigned long index, int rate, Func **args, int count, __attribute__((unused)) void *context)
{
    double sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += func_eval(args[i], index, rate);
    }
    return sum;
}

Func *sum_n(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, sum_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

Func *sum(Func *a, Func *b)
{
    return sum_n(2, a, b);
}

Func *sum_3(Func *a, Func *b, Func *c)
{
    return sum_n(3, a, b, c);
}

Func *sum_4(Func *a, Func *b, Func *c, Func *d)
{
    return sum_n(4, a, b, c, d);
}

#endif // COMPOSER_SUM_H
