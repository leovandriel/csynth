//
// rand.h - A xorshift random number generator
//
#ifndef CSYNTH_RAND_H
#define CSYNTH_RAND_H

#include <limits.h>
#include <math.h>
#include <stddef.h>

#define RAND_STATE_INIT 1082269761

static size_t rand_state_global = RAND_STATE_INIT;

static size_t rand_next(size_t reg)
{
    reg ^= reg << 13;
    reg ^= reg >> 7;
    reg ^= reg << 17;
    return reg;
}

size_t rand_unsigned_long()
{
    rand_state_global = rand_next(rand_state_global);
    return rand_state_global;
}

double rand_uniform()
{
    return (double)rand_unsigned_long() / (double)ULONG_MAX;
}

double rand_range(double left, double right)
{
    return (right - left) * rand_uniform() + left;
}

double rand_gauss(double muu, double sigma)
{
    return sigma * sqrt(-2.0 * log(rand_uniform())) * cos(rand_uniform() * M_PI * 2) + muu;
}

void rand_seed(size_t seed)
{
    rand_state_global = seed + RAND_STATE_INIT;
}

#endif // CSYNTH_RAND_H
