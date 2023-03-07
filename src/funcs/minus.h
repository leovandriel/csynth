#ifndef COMPOSER_MINUS_H
#define COMPOSER_MINUS_H

#include "../core/func.h"

double minus_eval(unsigned long index, double rate, Func **args, __attribute__((unused)) int count, __attribute__((unused)) void *context)
{
    double a = func_eval(args[0], index, rate);
    double b = func_eval(args[1], index, rate);
    return a - b;
}

Func *minus(Func *a, Func *b)
{
    return func_create(NULL, minus_eval, NULL, 0, NULL, 2, a, b);
}

#endif // COMPOSER_MINUS_H
