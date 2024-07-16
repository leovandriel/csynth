//
// uniform.h - Uniform noise function
//
// `uniform()` returns a random value in [-1, 1].
//
#ifndef CSYNTH_UNIFORM_H
#define CSYNTH_UNIFORM_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/rand.h"

static double uniform_eval(__U size_t count, __U Gen **args, __U Eval *eval, __U void *context)
{
    return rand_range(-1, 1);
}

Func *uniform_create(void)
{
    return func_create(NULL, uniform_eval, NULL, 0, NULL, FuncFlagNone, ARGS());
}

#endif // CSYNTH_UNIFORM_H
