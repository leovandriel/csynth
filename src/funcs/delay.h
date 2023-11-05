#ifndef COMPOSER_DELAY_H
#define COMPOSER_DELAY_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double time;
} DelayContext;

double delay_eval(Func **args, __attribute__((unused)) int count, double delta, void *_context)
{
    DelayContext *context = (DelayContext *)_context;
    double span = func_eval(args[1]);
    double output = 0.0;
    if (context->time >= span)
    {
        output = func_eval(args[0]);
    }
    context->time += delta;
    return output;
}

Func *delay(Func *input, Func *duration)
{
    return func_create(NULL, delay_eval, NULL, sizeof(DelayContext), NULL, 2, input, duration);
}

#endif // COMPOSER_DELAY_H
