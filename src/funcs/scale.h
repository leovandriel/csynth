#ifndef COMPOSER_SCALE_H
#define COMPOSER_SCALE_H

#include "../core/func.h"

double scale_eval(unsigned long index, int rate, Func **args, __attribute__((unused)) int count, __attribute__((unused)) void *_context)
{
    double input = func_eval(args[0], index, rate);
    double scale = func_eval(args[1], index, rate);
    double output = input * scale;
    return output;
}

Func *scale(Func *input, Func *factor)
{
    return func_create(NULL, scale_eval, NULL, 0, NULL, 2, input, factor);
}

#endif // COMPOSER_SCALE_H
