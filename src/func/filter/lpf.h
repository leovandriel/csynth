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
#include "../time/times.h"

typedef struct
{
    double output;
} LowPassContext;

static double lpf_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    LowPassContext *context = (LowPassContext *)context_;
    double factor = 1 / (M_PI * 2 * gen_eval(args[0], eval)) + 1.0;
    double input = gen_eval(args[1], eval);
    double output = context->output;
    context->output = context->output + (input - context->output) / factor;
    return output;
}

Func *lpf_filter(Func *tick, Func *input)
{
    return func_create(NULL, lpf_eval, NULL, sizeof(LowPassContext), NULL, FuncFlagNone, FUNCS(tick, input));
}

#endif // CSYNTH_LPF_H
