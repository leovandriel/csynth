#ifndef COMPOSER_SUM_H
#define COMPOSER_SUM_H

#include <stdarg.h>

#include "../core/func.h"

double sum_eval(Gen **args, int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += gen_eval(args[i]);
    }
    return sum;
}

Func *sum_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, sum_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

#define sum(...) sum_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__)

#endif // COMPOSER_SUM_H
