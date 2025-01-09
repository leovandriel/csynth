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
 * @brief Create a function that samples from an input function once and returns
 * that value as a constant.
 *
 * The function evaluates the input function exactly once when first called,
 * stores the result, and returns that same sampled value on all subsequent
 * calls. This creates a constant signal from a potentially varying input.
 *
 * Can be used to sample a control signal at a specific point in time, like
 * capturing a random detune value when a note is pressed, or freezing an LFO at
 * a particular phase. The sampled value persists until the function is reset.
 *
 * @param input Input function to sample from. Common inputs include: - Random
 *              generators for per-note variation - LFOs to capture specific
 *              modulation values - Control signals to freeze their current
 *              state
 *
 * @return Func* Sample function that outputs the constant sampled value
 */
Func *sample_create(Func *input)
{
    return func_create(NULL, sample_eval, NULL, NULL, sizeof(SampleContext), NULL, FuncFlagStopReset, input);
}

#endif // CSYNTH_SAMPLE_H
