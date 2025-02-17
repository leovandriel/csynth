#ifndef CSYNTH_TRIANGLE_H
#define CSYNTH_TRIANGLE_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see triange_create */
typedef struct
{
    /** @brief Previous output value. */
    double last;
    /** @brief Direction of the triangle wave. */
    double direction;
} TriangleContext;

static double triangle_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    TriangleContext *context = (TriangleContext *)context_;
    double output = context->last;
    double tick = gen_eval(args[0], eval);
    double skew = gen_eval(args[1], eval);
    context->last += 4.0 / (skew + context->direction) * tick;
    if (context->direction * context->last > 1.0)
    {
        context->last = context->direction + (context->last - context->direction) * (skew + context->direction) / (skew - context->direction);
        context->direction = -context->direction;
    }
    return output;
}

/**
 * @brief Create a function that outputs a triangle wave oscillator.
 *
 * A triangle wave is a periodic waveform that linearly ramps up and down
 * between +1 and -1, creating a triangular shape. Unlike square waves, triangle
 * waves contain only odd harmonics that decrease in amplitude as 1/n^2,
 * resulting in a mellower sound with less high frequency content.
 *
 * The frequency of the wave is controlled by the tick parameter, which
 * specifies how many periods/cycles occur per sample. For example, to generate
 * a 440 Hz triangle wave at a 44.1 kHz sample rate, tick should be 440/44100 ≈
 * 0.00998.
 *
 * @param tick Function that controls the frequency in periods per sample.
 *            Frequency in Hz = tick * sample_rate
 * @param skew Value in [-1, 1], with 0 being a standard triangle wave, -1 and 1
 *             being a sawtooth wave.
 * @return Func* Triangle wave oscillator that outputs values between -1 and +1.
 */
Func *triangle_create(Func *tick, Func *skew)
{
    TriangleContext initial = {.direction = 1.0};
    return func_create(NULL, triangle_eval, NULL, NULL, sizeof(TriangleContext), &initial, FuncFlagNone, tick, skew);
}

#endif // CSYNTH_TRIANGLE_H
