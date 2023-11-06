//
// noise.h - Noise function
//
// `noise()` returns a random value in [-1, 1].
//
#ifndef CSYNTH_NOISE_H
#define CSYNTH_NOISE_H

#include <assert.h>
#include <stdlib.h>

#include "../core/func.h"

double noise_eval(__attribute__((unused)) Gen **args, __attribute__((unused)) int count, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    return 2.0 * rand() / RAND_MAX - 1.0;
}

Func *noise()
{
    return func_create(NULL, noise_eval, NULL, 0, NULL, 0);
}

void test_noise()
{
    for (int i = 0; i < 100; i++)
    {
        double v = gen_eval(gen_create(noise(), .1));
        assert(v < 1.0 && v > -1.0);
    }
}

#endif // CSYNTH_NOISE_H
