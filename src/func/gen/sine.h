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
 * @brief Create a function that outputs an approximate sine wave.
 *
 * Due to the cost of `sin`, the result is cached in a lookup table and
 * interpolated.
 *
 * @param tick Periods per sample.
 * @return Func* Sine function.
 */
Func *sine_create(Func *tick)
{
    return func_create(NULL, sine_eval, NULL, NULL, sizeof(SineContext), NULL, FuncFlagNone, tick);
}

#endif // CSYNTH_SINE_H
