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
 * @brief Create a function that implements a first-order low-pass filter. The
 *        filter attenuates high frequency components above the cutoff frequency
 *        while allowing low frequency components to pass through. The cutoff
 *        frequency is determined by the tick parameter, where cutoff =
 *        1/(2π*tick). The filter has a slope of -6 dB/octave above the cutoff
 *        frequency.
 *
 * @param tick Periods per sample, controls the cutoff frequency. Higher values
 *             result in a lower cutoff frequency.
 * @param input Input signal to be filtered.
 * @return Func* Low-pass filter function that processes the input signal.
 */
Func *lpf_create(Func *tick, Func *input)
{
    return func_create(NULL, lpf_eval, NULL, NULL, sizeof(LowPassContext), NULL, FuncFlagNone, tick, input);
}

#endif // CSYNTH_LPF_H
