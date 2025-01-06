#ifndef CSYNTH_GAUSS_H
#define CSYNTH_GAUSS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/random.h"

/** @see gauss_create */
typedef struct
{
    /** @brief Random number generator. */
    Random random;
} GaussContext;

static double gauss_eval(__U size_t count, __U Gen **args, __U Eval *eval, __U void *context_)
{
    GaussContext *context = (GaussContext *)context_;
    return random_gauss(&context->random);
}

/**
 * @brief Create a function that outputs normal distributed pseudo random
 * values, i.e. Gaussian noise.
 *
 * Gaussian noise follows a normal distribution with mean 0 and standard deviation 1,
 * creating noise that clusters around the center value with decreasing probability
 * toward the extremes. This produces a more natural sounding noise compared to
 * uniform white noise, as it better matches many real-world random processes.
 *
 * The output follows the standard normal distribution N(0,1), meaning approximately:
 * - 68% of values fall within ±1.0
 * - 95% of values fall within ±2.0
 * - 99.7% of values fall within ±3.0
 *
 * Each call returns a new random value using a dedicated random number generator
 * initialized with seed 0. The values are independent of previous outputs.
 *
 * Common uses include:
 * - Natural sounding noise effects
 * - Dithering and adding randomness
 * - Simulating random fluctuations
 * - Creating "pink noise" when filtered
 *
 * @return Func* Gaussian noise function that outputs normally distributed values.
 */
Func *gauss_create(void)
{
    GaussContext initial = {.random = random_create(0)};
    return func_create(NULL, gauss_eval, NULL, NULL, sizeof(GaussContext), &initial, FuncFlagNone);
}

#endif // CSYNTH_GAUSS_H
