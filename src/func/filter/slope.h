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
 * @brief Create a function that limits the slope of the input signal.
 *
 * @param tick Periods per sample.
 * @param input Input signal.
 * @return Func* Slope function.
 */
Func *slope_create(Func *tick, Func *input)
{
    return func_create(NULL, slope_eval, NULL, sizeof(SlopeContext), NULL, FuncFlagNone, tick, input);
}

#endif // CSYNTH_SLOPE_H
