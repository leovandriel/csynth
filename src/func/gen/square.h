#ifndef CSYNTH_SQUARE_H
#define CSYNTH_SQUARE_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see square_create */
typedef struct
{
    /** @brief Time offset within 1s period. */
    double phase;
    /** @brief Current output value. */
    double output;
} SquareContext;

static double square_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SquareContext *context = (SquareContext *)context_;
    if (context->phase >= 0.5)
    {
        context->phase -= 0.5;
        context->output = -context->output;
    }
    double tick = gen_eval(args[0], eval);
    context->phase += tick;
    return context->output;
}

/**
 * @brief Create a function that outputs a square wave oscillator.
 *
 * A square wave alternates between two fixed values (+1 and -1) with equal time
 * spent at each level, creating a rectangular waveform. The wave contains only
 * odd harmonics that decrease in amplitude as 1/n, making it useful for
 * synthesizing hollow or reedy tones.
 *
 * The frequency of the wave is controlled by the tick parameter, which specifies
 * how many periods/cycles occur per sample. For example, to generate a 440 Hz
 * square wave at a 44.1 kHz sample rate, tick should be 440/44100 ≈ 0.00998.
 *
 * @param tick Function that controls the frequency in periods per sample.
 *            Frequency in Hz = tick * sample_rate
 * @return Func* Square wave oscillator that outputs values alternating between +1 and -1.
 */
Func *square_create(Func *tick)
{
    SquareContext initial = {.output = 1.0};
    return func_create(NULL, square_eval, NULL, NULL, sizeof(SquareContext), &initial, FuncFlagNone, tick);
}

#endif // CSYNTH_SQUARE_H
