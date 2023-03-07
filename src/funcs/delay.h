#ifndef COMPOSER_DELAY_H
#define COMPOSER_DELAY_H

#include "../core/func.h"

double delay_eval(unsigned long index, int rate, Func **args, __attribute__((unused)) int count, __attribute__((unused)) void *context)
{
    unsigned long span = func_eval(args[1], index, rate) * rate;
    double output = 0.0;
    if (index >= span)
    {
        output = func_eval(args[0], index, rate);
    }
    return output;
}

Func *delay(Func *input, Func *duration)
{
    return func_create(NULL, delay_eval, NULL, 0, NULL, 2, input, duration);
}

#endif // COMPOSER_DELAY_H
