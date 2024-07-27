#ifndef CSYNTH_LPF_H
#define CSYNTH_LPF_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see lpf_create */
typedef struct
{
    /** @brief Last output value. */
    double output;
} LowPassContext;

static double lpf_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    LowPassContext *context = (LowPassContext *)context_;
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    double output = context->output;
    double factor = 1.0 / (M_PI * 2 * tick) + 1.0;
    context->output = context->output + (input - context->output) / factor;
    return output;
}

/**
 * @brief Create a function that implements a first-order low-pass filter.
 *
 * @param tick Periods per sample.
 * @param input Input signal.
 * @return Func* Low-pass filter function.
 */
Func *lpf_create(Func *tick, Func *input)
{
    return func_create(NULL, lpf_eval, NULL, sizeof(LowPassContext), NULL, FuncFlagNone, tick, input);
}

#endif // CSYNTH_LPF_H
