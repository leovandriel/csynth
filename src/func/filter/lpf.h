//
// lpf.h - A first-order low-pass filter
//
// `lpf(input, frequency)` with input and frequency functions.
//
#ifndef CSYNTH_LPF_H
#define CSYNTH_LPF_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

typedef struct
{
    double output;
} LowPassContext;

static double lpf_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    LowPassContext *context = (LowPassContext *)context_;
    double input = gen_eval(args[0], eval);
    double frequency = gen_eval(args[1], eval);
    double factor = 1 / (M_PI * 2 * frequency * eval.step[EvalStepAudio]) + 1.0;
    double output = context->output;
    context->output = context->output + (input - context->output) / factor;
    return output;
}

Func *lpf(Func *input, Func *frequency)
{
    return func_create(NULL, lpf_eval, NULL, sizeof(LowPassContext), NULL, FuncFlagNone, FUNCS(input, frequency));
}

Func *lpf_(Func *input, double frequency) { return lpf(input, const_(frequency)); }

#endif // CSYNTH_LPF_H
