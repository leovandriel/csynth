#ifndef CSYNTH_SAW_H
#define CSYNTH_SAW_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see saw_create */
typedef struct
{
    /** @brief Last output value. */
    double output;
} SawContext;

static double saw_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SawContext *context = (SawContext *)context_;
    double output = context->output;
    double tick = gen_eval(args[0], eval);
    context->output += 2.0 * tick;
    if (context->output > 1.0)
    {
        context->output -= 2.0;
    }
    return output;
}

/**
 * @brief Create a function that outputs a sawtooth wave oscillator.
 *
 * A sawtooth wave linearly increases from -1 to 1 and then instantly drops back
 * to -1, creating a characteristic "ramp" waveform. The wave has rich harmonic
 * content with both even and odd harmonics, making it useful for synthesizing
 * bright, buzzy tones.
 *
 * The frequency of the wave is controlled by the tick parameter, which specifies
 * how many periods/cycles occur per sample. For example, to generate a 440 Hz
 * sawtooth wave at a 44.1 kHz sample rate, tick should be 440/44100 ≈ 0.00998.
 *
 * @param tick Function that controls the frequency in periods per sample.
 *            Frequency in Hz = tick * sample_rate
 * @return Func* Sawtooth wave oscillator that outputs values in the range [-1, 1].
 */
Func *saw_create(Func *tick)
{
    return func_create(NULL, saw_eval, NULL, NULL, sizeof(SawContext), NULL, FuncFlagNone, tick);
}

#endif // CSYNTH_SAW_H
