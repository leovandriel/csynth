#ifndef CSYNTH_SINE_H
#define CSYNTH_SINE_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see sine_create */
typedef struct
{
    /** @brief Current output value of the sine wave. */
    double output;
    /** @brief Previous output value for calculating next sample. */
    double prev;
    /** @brief Coefficient used in the recurrence relation. */
    double coeff;
    /** @brief Last tick value used to detect frequency changes. */
    double last_tick;
} SineContext;

static double sine_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SineContext *context = (SineContext *)context_;
    double tick = gen_eval(args[0], eval);
    if (!tick)
    {
        return context->output;
    }
    if (eval == NULL || eval->compute_flag)
    {
        double cas = 0;
        if (context->last_tick)
        {
            double omega = 2 * M_PI * context->last_tick;
            cas = (context->output * cos(omega) - context->prev) / sin(omega);
        }
        else
        {
            double sign = context->output < context->prev ? -1 : 1;
            cas = sign * sqrt(1 - context->output * context->output);
        }
        double omega = 2 * M_PI * tick;
        context->prev = context->output * cos(omega) - cas * sin(omega);
        context->coeff = 2 * cos(omega);
        context->last_tick = tick;
    }
    double output = context->output;
    context->output = output * context->coeff - context->prev;
    context->prev = output;
    return output;
}

/**
 * @brief Create a function that outputs an approximate sine wave using a
 * recursive algorithm.
 *
 * This implementation uses a second-order recurrence relation to generate sine
 * waves efficiently without calling sin() for each sample. The algorithm
 * maintains phase coherence when frequency changes occur.
 *
 * The recurrence relation used is: y[n] = 2cos(ω)y[n-1] - y[n-2] where ω = 2π *
 *     tick is the angular frequency.
 *
 * When the frequency changes, the algorithm computes a new coefficient and
 * maintains continuity by solving for the quadrature component (cosine) of the
 * wave using the current and previous samples. This preserves both amplitude
 * and phase.
 *
 * The output is a high-quality sine wave with minimal computational overhead,
 * making it suitable for real-time audio synthesis. The wave maintains constant
 * amplitude of 1.0 regardless of frequency.
 *
 * @param tick Function that controls frequency in periods per sample. To get
 *            frequency in Hz, multiply by sample rate: frequency = tick *
 *            sample_rate
 * @return Func* Sine oscillator that outputs values in range [-1, 1].
 */
Func *sine_create(Func *tick)
{
    return func_create(NULL, sine_eval, NULL, NULL, sizeof(SineContext), NULL, FuncFlagNone, tick);
}

#endif // CSYNTH_SINE_H
