#ifndef CSYNTH_RAND_H
#define CSYNTH_RAND_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/random.h"

static double rand_eval(__U size_t count, __U Gen **args, __U Eval *eval, __U void *context_)
{
    return random_uniform(&random_global);
}

/**
 * @brief Create a function that outputs randly distributed pseudo random
 * values on interval [-1, 1], i.e. white noise.
 *
 * @return Func* rand noise function.
 */
Func *rand_create(void)
{
    return func_create(NULL, rand_eval, NULL, NULL, 0, NULL, FuncFlagNone);
}

#endif // CSYNTH_RAND_H
