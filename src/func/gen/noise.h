//
// noise.h - Noise function
//
// `noise()` returns a random value in [-1, 1].
//
#ifndef CSYNTH_NOISE_H
#define CSYNTH_NOISE_H

#include <stdlib.h>

#include "../../util/test.h"
#include "../../core/func.h"
#include "../../util/rand.h"

static double noise_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    return rand_range(-1, 1);
}

Func *noise()
{
    return func_create(NULL, noise_eval, NULL, 0, NULL, 0);
}

void test_noise()
{
    for (int i = 0; i < 100; i++)
    {
        assert_gen_range(gen_create(noise(), .1), -1.0, 1.0);
    }
}

#endif // CSYNTH_NOISE_H
