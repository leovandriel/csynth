//
// delay.h - A time delay on the sampling of a function
//
// `delay(input, duration)` waits duration (a function) seconds before it starts
// sampling the input function.
//
#ifndef COMPOSER_DELAY_H
#define COMPOSER_DELAY_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double time;
} DelayContext;

double delay_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    DelayContext *context = (DelayContext *)_context;
    double span = gen_eval(args[1]);
    double output = 0.0;
    while (context->time >= span)
    {
        output = gen_eval(args[0]);
        context->time -= delta;
    }
    context->time += delta;
    return output;
}

Func *delay(Func *input, Func *duration)
{
    return func_create(NULL, delay_eval, NULL, sizeof(DelayContext), NULL, 2, input, duration);
}

#define skip(input, duration) delay(input, neg(duration))

#endif // COMPOSER_DELAY_H
