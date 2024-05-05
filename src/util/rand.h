//
// rand.h - A xorshift random number generator
//
#ifndef CSYNTH_RAND_H
#define CSYNTH_RAND_H

#include <limits.h>

#include "./test.h"

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

void test_rand()
{
    rand_seed(0);
    assert(rand_unsigned_long() == 1152992998833853505UL);
    assert(rand_unsigned_long() == 11177516664432764457UL);
    assert(rand_unsigned_long() == 17678023832001937445UL);
    assert(rand_range(0, 1) == 0.52362249432221674716);
    assert(rand_range(1, 2) == 1.96362799473474725076);
    assert(rand_range(-3, 7) == 3.33880676916069862869);
}

#endif // CSYNTH_RAND_H
