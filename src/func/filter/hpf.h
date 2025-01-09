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
 * @brief Create a function that implements a first-order high-pass filter. The
 *        filter attenuates low frequency components below the cutoff frequency
 *        while allowing high frequency components to pass through. The cutoff
 *        frequency is determined by the tick parameter, where cutoff =
 *        1/(2π*tick). The filter has a slope of +6 dB/octave above the cutoff
 *        frequency.
 *
 * @param tick Periods per sample, controls the cutoff frequency. Higher values
 *             result in a lower cutoff frequency.
 * @param input Input signal to be filtered.
 * @return Func* High-pass filter function that processes the input signal.
 */
Func *hpf_create(Func *tick, Func *input)
{
    return func_create(NULL, hpf_eval, NULL, NULL, sizeof(HighPassContext), NULL, FuncFlagNone, tick, input);
}

#endif // CSYNTH_HPF_H
