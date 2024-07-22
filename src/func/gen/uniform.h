//
// uniform.h - Uniform noise function
//
// `uniform()` returns a random value in [-1, 1].
//
#ifndef CSYNTH_UNIFORM_H
#define CSYNTH_UNIFORM_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/random.h"

typedef struct
{
    Random random;
} UniformContext;

static double uniform_eval(__U size_t count, __U Gen **args, __U Eval *eval, __U void *context_)
{
    UniformContext *context = (UniformContext *)context_;
    return random_range(&context->random, -1, 1);
}

Func *uniform_create(void)
{
    UniformContext initial = {.random = random_create(0)};
    return func_create(NULL, uniform_eval, NULL, sizeof(UniformContext), &initial, FuncFlagNone, );
}

#endif // CSYNTH_UNIFORM_H
