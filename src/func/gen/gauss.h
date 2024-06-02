//
// gauss.h - Gaussian noise function
//
// `gauss()` returns a random value in [-inf, inf], approximately normal distributed.
//
#ifndef CSYNTH_GAUSS_H
#define CSYNTH_GAUSS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/rand.h"

static double gauss_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    return rand_gauss(0, 1);
}

Func *gauss()
{
    return func_create(NULL, gauss_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 0);
}

#endif // CSYNTH_GAUSS_H
