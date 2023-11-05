#ifndef COMPOSER_HIGHPASS_H
#define COMPOSER_HIGHPASS_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double input;
    double output;
} HighpassContext;

double highpass_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    HighpassContext *context = (HighpassContext *)_context;
    double input = gen_eval(args[0]);
    double frequency = gen_eval(args[1]);
    double factor = (frequency * 2.0 * M_PI * delta) + 1.0;
    context->output = (context->output + input - context->input) / factor;
    context->input = input;
    return context->output;
}

Func *highpass(Func *input, Func *frequency)
{
    return func_create(NULL, highpass_eval, NULL, sizeof(HighpassContext), NULL, 2, input, frequency);
}

#endif // COMPOSER_HIGHPASS_H
