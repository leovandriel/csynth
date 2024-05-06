//
// noise.h - Noise function
//
// `noise()` returns a random value in [-1, 1].
//
#ifndef CSYNTH_NOISE_H
#define CSYNTH_NOISE_H

#include "../../core/func.h"
#include "../../util/rand.h"

static double noise_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    return rand_range(-1, 1);
}

Func *noise()
{
    return func_create(NULL, noise_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 0);
}

#endif // CSYNTH_NOISE_H
