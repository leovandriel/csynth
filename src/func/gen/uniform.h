#ifndef CSYNTH_UNIFORM_H
#define CSYNTH_UNIFORM_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/random.h"

/** @see uniform_create */
typedef struct
{
    /** @brief Random number generator. */
    Random random;
} UniformContext;

static double uniform_eval(__U size_t count, __U Gen **args, __U Eval *eval, __U void *context_)
{
    UniformContext *context = (UniformContext *)context_;
    return random_uniform_range(&context->random, -1, 1);
}

/**
 * @brief Create a function that outputs uniformly distributed pseudo random
 * values on interval [-1, 1], i.e. white noise.
 *
 * White noise contains equal power across all frequencies, making it useful as
 * a basic noise source or for generating other types of noise through filtering.
 * Each call to the function returns a new random value independent of previous
 * values, using a dedicated random number generator initialized with seed 0.
 *
 * The output range of [-1, 1] means the noise can be directly mixed with other
 * audio signals without additional scaling. For noise with different ranges,
 * combine this with scaling functions.
 *
 * @return Func* Uniform noise function that outputs values in the range [-1, 1].
 */
Func *uniform_create(void)
{
    UniformContext initial = {.random = random_create(0)};
    return func_create(NULL, uniform_eval, NULL, NULL, sizeof(UniformContext), &initial, FuncFlagNone);
}

#endif // CSYNTH_UNIFORM_H
