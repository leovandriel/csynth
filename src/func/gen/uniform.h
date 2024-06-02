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

static double uniform_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    return rand_range(-1, 1);
}

Func *uniform()
{
    return func_create(NULL, uniform_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 0);
}

#endif // CSYNTH_UNIFORM_H
