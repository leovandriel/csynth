//
// minus.h - Minus function
//
// `minus(a, b)` returns the difference a - b.
//
#ifndef COMPOSER_MINUS_H
#define COMPOSER_MINUS_H

#include "../core/func.h"

double minus_eval(Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double a = gen_eval(args[0]);
    double b = gen_eval(args[1]);
    return a - b;
}

Func *minus(Func *a, Func *b)
{
    return func_create(NULL, minus_eval, NULL, 0, NULL, 2, a, b);
}

#endif // COMPOSER_MINUS_H
