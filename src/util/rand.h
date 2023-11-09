//
// rand.h - A xorshift random number generator
//
#ifndef CSYNTH_RAND_H
#define CSYNTH_RAND_H

#include <limits.h>

#include "./test.h"

static unsigned long rand_state = 1082269761;

unsigned long rand_next(unsigned long x)
{
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

unsigned long rand_unsigned_long()
{
    rand_state = rand_next(rand_state);
    return rand_state;
}

double rand_double()
{
    return rand_unsigned_long() / (double)ULONG_MAX;
}

void rand_seed(unsigned long seed)
{
    rand_state = seed + 1082269761;
}

void test_rand()
{
    rand_seed(0);
    assert(rand_unsigned_long() == 1152992998833853505UL);
    assert(rand_unsigned_long() == 11177516664432764457UL);
    assert(rand_unsigned_long() == 17678023832001937445UL);
    assert(rand_double() == 0.52362249432221674716);
    assert(rand_double() == 0.96362799473474713974);
    assert(rand_double() == 0.63388067691606986287);
}

#endif // CSYNTH_RAND_H
