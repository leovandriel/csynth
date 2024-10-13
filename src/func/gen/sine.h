#ifndef CSYNTH_SINE_H
#define CSYNTH_SINE_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see sine_create */
typedef struct
{
    /** @brief Phase offset within 1s period. */
    double phase;
} SineContext;

static double sine_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SineContext *context = (SineContext *)context_;
    double output = sin(context->phase * 2 * M_PI);
    double tick = gen_eval(args[0], eval);
    context->phase = fmod(context->phase + tick, 1.0);
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
