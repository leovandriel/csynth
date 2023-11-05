//
// high_pass.h - A first-order high-pass filter
//
// `high_pass(input, frequency)` with input and frequency functions.
//
#ifndef COMPOSER_HIGH_PASS_H
#define COMPOSER_HIGH_PASS_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double input;
    double output;
} HighPassContext;

double high_pass_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    HighPassContext *context = (HighPassContext *)_context;
    double input = gen_eval(args[0]);
    double frequency = gen_eval(args[1]);
    double factor = (frequency * 2.0 * M_PI * delta) + 1.0;
    context->output = (context->output + input - context->input) / factor;
    context->input = input;
    return context->output;
}

Func *high_pass(Func *input, Func *frequency)
{
    return func_create(NULL, high_pass_eval, NULL, sizeof(HighPassContext), NULL, 2, input, frequency);
}

#endif // COMPOSER_HIGH_PASS_H
