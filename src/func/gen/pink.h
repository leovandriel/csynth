#ifndef CSYNTH_PINK_H
#define CSYNTH_PINK_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/random.h"

static const double PINK_A[] = {0.99886, 0.99332, 0.969, 0.8665, 0.55, -0.7616};
static const double PINK_B[] = {0.0555179, 0.0750759, 0.153852, 0.3104856, 0.5329522, -0.016898};

/** @see pink_create */
typedef struct
{
    /** @brief Random number generator. */
    Random random;
    /** @brief Filter state. */
    double b__[6];
    /** @brief Last output value. */
    double last;
} PinkContext;

static double pink_eval(__U size_t count, __U Gen **args, __U Eval *eval, __U void *context_)
{
    PinkContext *context = (PinkContext *)context_;
    double white = random_uniform_range(&context->random, -1, 1);
    double sum = context->last * 0.115926;
    for (size_t i = 0; i < 6; i++)
    {
        context->b__[i] = PINK_A[i] * context->b__[i] + white * PINK_B[i];
        sum += context->b__[i];
    }
    context->last = white;
    return (sum + white * 0.5362) * 0.11;
}

/**
 * @brief Create a function that approximates pink noise, using an array of
 * first order low pass filters.
 *
 * Pink noise has a power spectral density that decreases by 3 dB per octave,
 * meaning it has equal energy per octave. This implementation uses six cascaded
 * first-order low-pass filters with carefully chosen coefficients to
 * approximate the 1/f spectrum characteristic of pink noise.
 *
 * The algorithm generates white noise and processes it through the filter
 * array, combining the outputs with specific weights. The result closely
 * matches the spectral properties of pink noise while being computationally
 * efficient.
 *
 * @return Func* Pink noise function that outputs values roughly in the range
 * [-1, 1].
 */
Func *pink_create(void)
{
    PinkContext initial = {.random = random_create(0)};
    return func_create(NULL, pink_eval, NULL, NULL, sizeof(PinkContext), &initial, FuncFlagNone);
}

#endif // CSYNTH_PINK_H
