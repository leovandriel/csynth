//
// rand.h - A xorshift random number generator
//
#ifndef CSYNTH_RAND_H
#define CSYNTH_RAND_H

#include <limits.h>
#include <math.h>
#include <stddef.h>

#define RAND_STATE_INIT 1082269761

typedef struct
{
    size_t state;
} Random;

static size_t random_next(size_t reg)
{
    reg ^= reg << 13;
    reg ^= reg >> 7;
    reg ^= reg << 17;
    return reg;
}

size_t random_unsigned_long(Random *random)
{
    random->state = random_next(random->state);
    return random->state;
}

double random_uniform(Random *random)
{
    return (double)random_unsigned_long(random) / (double)ULONG_MAX;
}

double random_range(Random *random, double left, double right)
{
    return (right - left) * random_uniform(random) + left;
}

double random_gauss(Random *random, double muu, double sigma)
{
    return sigma * sqrt(-2.0 * log(random_uniform(random))) * cos(random_uniform(random) * M_PI * 2) + muu;
}

Random random_create(size_t seed)
{
    return (Random){.state = seed + RAND_STATE_INIT};
}

#endif // CSYNTH_RAND_H
