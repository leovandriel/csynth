#ifndef COMPOSER_RATE_H
#define COMPOSER_RATE_H

#include "../core/func.h"

double rate_eval(unsigned long index, double rate, Func **args, __attribute__((unused)) int count, __attribute__((unused)) void *context)
{
    double multiplier = func_eval(args[1], index, rate);
    double output = func_eval(args[0], index, rate / multiplier);
    return output;
}

Func *rate(Func *input, Func *multiplier)
{
    return func_create(NULL, rate_eval, NULL, 0, NULL, 2, input, multiplier);
}

#endif // COMPOSER_RATE_H
