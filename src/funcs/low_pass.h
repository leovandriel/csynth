#ifndef COMPOSER_LOW_PASS_H
#define COMPOSER_LOW_PASS_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double output;
} LowPassContext;

double low_pass_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    LowPassContext *context = (LowPassContext *)_context;
    double input = gen_eval(args[0]);
    double frequency = gen_eval(args[1]);
    double factor = 1 / (delta * frequency * 2.0 * M_PI) + 1.0;
    context->output = context->output + (input - context->output) / factor;
    return context->output;
}

Func *low_pass(Func *input, Func *frequency)
{
    return func_create(NULL, low_pass_eval, NULL, sizeof(LowPassContext), NULL, 2, input, frequency);
}

#endif // COMPOSER_LOW_PASS_H
