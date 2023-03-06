#ifndef COMPOSER_MUL_H
#define COMPOSER_MUL_H

#include <stdarg.h>

#include "../core/func.h"

double mul_eval(unsigned long index, int rate, Func **args, int count, __attribute__((unused)) void *context)
{
    double output = 1.0;
    for (int i = 0; i < count; i++)
    {
        output *= func_eval(args[i], index, rate);
    }
    return output;
}

Func *mul_n(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, mul_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

Func *mul(Func *a, Func *b)
{
    return mul_n(2, a, b);
}

Func *mul_3(Func *a, Func *b, Func *c)
{
    return mul_n(3, a, b, c);
}

Func *mul_4(Func *a, Func *b, Func *c, Func *d)
{
    return mul_n(4, a, b, c, d);
}

#endif // COMPOSER_MUL_H
