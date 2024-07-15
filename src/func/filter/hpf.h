//
// hpf.h - A first-order high-pass filter
//
// `hpf(input, frequency)` with input and frequency functions.
//
#ifndef CSYNTH_HPF_H
#define CSYNTH_HPF_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double input;
    double output;
} HighPassContext;

static double hpf_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    HighPassContext *context = (HighPassContext *)context_;
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    double output = context->output;
    double factor = (M_PI * 2 * tick) + 1.0;
    context->output = (context->output + input - context->input) / factor;
    context->input = input;
    return output;
}

Func *hpf_create(Func *tick, Func *input)
{
    return func_create(NULL, hpf_eval, NULL, sizeof(HighPassContext), NULL, FuncFlagNone, ARGS(tick, input));
}

#endif // CSYNTH_HPF_H
