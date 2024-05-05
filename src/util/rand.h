//
// rand.h - A xorshift random number generator
//
#ifndef CSYNTH_RAND_H
#define CSYNTH_RAND_H

#include <limits.h>

#define RAND_STATE_INIT 1082269761

static unsigned long rand_state_int = RAND_STATE_INIT;

unsigned long rand_next(unsigned long x)
{
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

unsigned long rand_unsigned_long()
{
    rand_state_int = rand_next(rand_state_int);
    return rand_state_int;
}

double rand_range(double a, double b)
{
    return (b - a) * (rand_unsigned_long() / (double)ULONG_MAX) + a;
}

void rand_seed(unsigned long seed)
{
    rand_state_int = seed + RAND_STATE_INIT;
}

#endif // CSYNTH_RAND_H
