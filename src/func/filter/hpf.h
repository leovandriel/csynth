#ifndef CSYNTH_HPF_H
#define CSYNTH_HPF_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see hpf_create */
typedef struct
{
    /** @brief Last input value. */
    double input;
    /** @brief Last output value. */
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

/**
 * @brief Create a function that implements a first-order high-pass filter.
 *
 * @param tick Periods per sample.
 * @param input Input signal.
 * @return Func* High-pass filter function.
 */
Func *hpf_create(Func *tick, Func *input)
{
    return func_create(NULL, hpf_eval, NULL, NULL, sizeof(HighPassContext), NULL, FuncFlagNone, tick, input);
}

#endif // CSYNTH_HPF_H
