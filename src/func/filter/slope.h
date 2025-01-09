#ifndef CSYNTH_SLOPE_H
#define CSYNTH_SLOPE_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see slope_create */
typedef struct
{
    /** @brief Last output value. */
    double last;
} SlopeContext;

static double slope_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SlopeContext *context = (SlopeContext *)context_;
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    double diff = input - context->last;
    if (diff > tick)
    {
        diff = tick;
    }
    else if (diff < -tick)
    {
        diff = -tick;
    }
    double output = context->last + diff;
    context->last = output;
    return output;
}

/**
 * @brief Create a function that limits the slope (rate of change) of the input
 *        signal. The function ensures that the output signal cannot change
 *        faster than the specified tick rate. When the input changes more
 *        rapidly than the tick rate, the output will smoothly ramp at the
 *        maximum allowed rate. This creates a slew limiter or portamento effect
 *        that can smooth out sudden changes in the input signal.
 *
 * @param tick Periods per sample, controls the maximum rate of change. Higher
 *             values result in slower transitions, while lower values allow
 *             faster changes. For example, a tick value of 0.01 limits changes
 *             to 1% per sample.
 * @param input Input signal to be slope limited. Common uses include: - Pitch
 *              signals to create portamento effects - Control signals to smooth
 *              parameter changes - Audio signals for special effects
 * @return Func* Slope-limited function that processes the input signal with
 *               controlled rate of change.
 */
Func *slope_create(Func *tick, Func *input)
{
    return func_create(NULL, slope_eval, NULL, NULL, sizeof(SlopeContext), NULL, FuncFlagNone, tick, input);
}

#endif // CSYNTH_SLOPE_H
