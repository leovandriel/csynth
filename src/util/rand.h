//
// rand.h - A xorshift random number generator
//
#ifndef CSYNTH_RAND_H
#define CSYNTH_RAND_H

#include <limits.h>

#include "../util/math.h"

#define RAND_STATE_INIT 1082269761

static unsigned long rand_state_int = RAND_STATE_INIT;

unsigned long rand_next(unsigned long reg)
{
    reg ^= reg << 13;
    reg ^= reg >> 7;
    reg ^= reg << 17;
    return reg;
}

unsigned long rand_unsigned_long()
{
    rand_state_int = rand_next(rand_state_int);
    return rand_state_int;
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
    return sigma * sqrt(-2.0 * log(rand_uniform())) * cos(rand_uniform() * PI_M_2) + muu;
}

void rand_seed(unsigned long seed)
{
    rand_state_int = seed + RAND_STATE_INIT;
}

#endif // CSYNTH_RAND_H
