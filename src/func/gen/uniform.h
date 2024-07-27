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
    return random_range(&context->random, -1, 1);
}

/**
 * @brief Create a function that outputs uniformly distributed pseudo random
 * values on interval [-1, 1], i.e. white noise.
 *
 * @return Func* Uniform noise function.
 */
Func *uniform_create(void)
{
    UniformContext initial = {.random = random_create(0)};
    return func_create(NULL, uniform_eval, NULL, sizeof(UniformContext), &initial, FuncFlagNone, );
}

#endif // CSYNTH_UNIFORM_H
