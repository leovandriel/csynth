#ifndef COMPOSER_ADD_H
#define COMPOSER_ADD_H

#include <stdarg.h>

#include "../core/func.h"

double add_eval(Gen **args, int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += gen_eval(args[i]);
    }
    return sum;
}

Func *add_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, add_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

#define add(...) add_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__)

#endif // COMPOSER_ADD_H
