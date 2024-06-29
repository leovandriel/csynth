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
#include "../gen/const.h"

typedef struct
{
    double input;
    double output;
} HighPassContext;

static double hpf_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    HighPassContext *context = (HighPassContext *)context_;
    double input = gen_eval(args[0], eval);
    double frequency = gen_eval(args[1], eval);
    double factor = (M_PI * 2 * frequency * eval.tick[EvalTickPitch]) + 1.0;
    double output = context->output;
    context->output = (context->output + input - context->input) / factor;
    context->input = input;
    return output;
}

Func *hpf(Func *input, Func *frequency)
{
    return func_create(NULL, hpf_eval, NULL, sizeof(HighPassContext), NULL, FuncFlagNone, FUNCS(input, frequency));
}

Func *hpf_(Func *input, double frequency) { return hpf(input, const_(frequency)); }

#endif // CSYNTH_HPF_H
