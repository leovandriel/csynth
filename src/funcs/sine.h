#ifndef COMPOSER_SINE_H
#define COMPOSER_SINE_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double output;
    double direction;
} SineContext;

double sine_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    SineContext *context = (SineContext *)_context;
    double frequency = gen_eval(args[0]);
    double factor = 2.0 * M_PI * frequency * delta;
    double next = asin(context->output) * context->direction + factor;
    context->output = sin(context->direction * next);
    context->direction = (int)round(next / M_PI) % 2 == 0 ? context->direction : -context->direction;
    return context->output;
}

Func *sine(Func *frequency)
{
    SineContext initial = (SineContext){
        .direction = 1.0,
    };
    return func_create(NULL, sine_eval, NULL, sizeof(SineContext), &initial, 1, frequency);
}

#endif // COMPOSER_SINE_H
