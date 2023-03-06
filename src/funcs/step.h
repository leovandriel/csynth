#ifndef COMPOSER_STEP_H
#define COMPOSER_STEP_H

#include "../core/func.h"

double step_eval(unsigned long index, int rate, Func **args, __attribute__((unused)) int count, __attribute__((unused)) void *_context)
{
    unsigned long span = func_eval(args[0], index, rate) * rate;
    return index < span ? 0.0 : 1.0;
}

Func *step(Func *at)
{
    return func_create(NULL, step_eval, NULL, 0, NULL, 1, at);
}

#endif // COMPOSER_STEP_H
