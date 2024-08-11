#ifndef CSYNTH_SAMPLE_H
#define CSYNTH_SAMPLE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/random.h"

typedef double (*random_cb)(Random *random);

/** @see sample_uniform_create */
typedef struct
{
    /** @brief Random number generator. */
    Random random;
    /** @brief Sampled value, for constant output. */
    double sample;
    /** @brief Callback function to generate random numbers. */
    random_cb cb;
} SampleContext;

static double sample_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    SampleContext *context = (SampleContext *)context_;
    if (context->sample == 0.0)
    {
        context->sample = context->cb(&context->random);
    }
    return context->sample;
}

/**
 * @brief Create a function that samples from a uniformly distributed and
 * returns that value as a constant.
 *
 * Can be used to sample a constant control signal, like detune on key press.
 *
 * @return Func* Sample function.
 */
Func *sample_uniform_create(void)
{
    SampleContext initial = {
        .random = random_create(0),
        .cb = random_uniform,
    };
    return func_create(NULL, sample_eval, NULL, NULL, sizeof(SampleContext), &initial, FuncFlagNone);
}

/**
 * @brief Create a function that samples from a normal distributed and
 * returns that value as a constant.
 *
 * Can be used to sample a constant control signal, like detune on key press.
 *
 * @return Func* Sample function.
 */
Func *sample_gauss_create(void)
{
    SampleContext initial = {
        .random = random_create(0),
        .cb = random_gauss,
    };
    return func_create(NULL, sample_eval, NULL, NULL, sizeof(SampleContext), &initial, FuncFlagNone);
}

#endif // CSYNTH_SAMPLE_H
