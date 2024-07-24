#ifndef CSYNTH_GAUSS_H
#define CSYNTH_GAUSS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/random.h"

typedef struct
{
    Random random;
} GaussContext;

static double gauss_eval(__U size_t count, __U Gen **args, __U Eval *eval, __U void *context_)
{
    GaussContext *context = (GaussContext *)context_;
    return random_gauss(&context->random, 0, 1);
}

/**
 * @brief Create a function that outputs normal distributed pseudo random
 * values, i.e. Gaussian noise.
 *
 * @return Func* Function object.
 */
Func *gauss_create(void)
{
    GaussContext initial = {.random = random_create(0)};
    return func_create(NULL, gauss_eval, NULL, sizeof(GaussContext), &initial, FuncFlagNone, );
}

#endif // CSYNTH_GAUSS_H
