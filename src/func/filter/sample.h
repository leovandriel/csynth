#ifndef CSYNTH_SAMPLE_H
#define CSYNTH_SAMPLE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/random.h"

/** @see sample */
typedef struct
{
    /** @brief Sampled value, for constant output. */
    double sample;
    /** @brief Whether the sample has been sampled. */
    bool sampled;
} SampleContext;

static double sample_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    SampleContext *context = (SampleContext *)context_;
    if (!context->sampled)
    {
        context->sampled = true;
        context->sample = gen_eval(args[0], eval);
    }
    return context->sample;
}

/**
 * @brief Create a function that samples from an input function and
 * returns that value as a constant.
 *
 * Can be used to sample a constant control signal, like detune on key press.
 *
 * @param input Input function to sample from, like a uniform random function.
 *
 * @return Func* Sample function.
 */
Func *sample_create(Func *input)
{
    return func_create(NULL, sample_eval, NULL, NULL, sizeof(SampleContext), NULL, FuncFlagStopReset, input);
}

#endif // CSYNTH_SAMPLE_H
