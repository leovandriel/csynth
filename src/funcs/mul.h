#ifndef COMPOSER_MUL_H
#define COMPOSER_MUL_H

#include <stdarg.h>

#include "../core/func.h"

double mul_eval(Func **args, int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double output = 1.0;
    for (int i = 0; i < count; i++)
    {
        output *= func_eval(args[i]);
    }
    return output;
}

Func *mul_args(int count, ...)
{
    va_list valist;
    va_start(valist, count);
    Func *func = func_create_va(NULL, mul_eval, NULL, 0, NULL, count, valist);
    va_end(valist);
    return func;
}

#define mul(...) mul_args((sizeof((Func *[]){__VA_ARGS__}) / sizeof(Func **)), __VA_ARGS__)

#endif // COMPOSER_MUL_H
