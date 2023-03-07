#ifndef COMPOSER_SAW_H
#define COMPOSER_SAW_H

#include "../core/func.h"

typedef struct
{
    double output;
} SawContext;

double saw_eval(unsigned long index, double rate, Func **args, __attribute__((unused)) int count, void *_context)
{
    SawContext *context = (SawContext *)_context;
    double frequency = func_eval(args[0], index, rate);
    context->output += 2.0 * frequency / rate;
    if (context->output > 1.0)
    {
        context->output -= 2.0;
    }
    return context->output;
}

Func *saw(Func *frequency)
{
    return func_create(NULL, saw_eval, NULL, sizeof(SawContext), NULL, 1, frequency);
}

#endif // COMPOSER_SAW_H
