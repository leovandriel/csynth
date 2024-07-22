//
// random.h - A xorshift random number generator
//
#ifndef CSYNTH_RANDOM_H
#define CSYNTH_RANDOM_H

#include <limits.h>
#include <math.h>
#include <stddef.h>

#define RAND_STATE_INIT 1082269761

typedef struct
{
    size_t state;
} Random;

/**
 * @brief Create a new Random struct with a given seed.
 *
 * @see RAND_STATE_INIT
 *
 * @param seed Seed for the random number generator, usually 0.
 * @return Random
 */
Random random_create(size_t seed)
{
    return (Random){.state = seed + RAND_STATE_INIT};
}

static size_t random_next(size_t reg)
{
    reg ^= reg << 13;
    reg ^= reg >> 7;
    reg ^= reg << 17;
    return reg;
}

/**
 * @brief Generate a random unsigned long (size_t), uniformly distributed.
 *
 * Uses the 64-bit Xorshift algorithm to generate a random unsigned long.
 *
 * @param random Random struct
 * @return size_t Random unsigned long
 */
size_t random_unsigned_long(Random *random)
{
    random->state = random_next(random->state);
    return random->state;
}

/**
 * @brief Generate a random number between 0 and 1, uniformly distributed.
 *
 * @param random Random struct
 * @return double Number in the interval [0, 1]
 */
double random_uniform(Random *random)
{
    return (double)random_unsigned_long(random) / (double)ULONG_MAX;
}

/**
 * @brief Generate a random number from a uniform distribution between lower and
 * upper.
 *
 * Uses the random_uniform function to generate a random number in the interval
 * [0, 1] and scales it to the interval [lower, upper].
 *
 * @param random Random struct
 * @param lower Lower bound
 * @param upper Uppper bound
 * @return double Number in the interval [lower, upper]
 */
double random_range(Random *random, double lower, double upper)
{
    return (upper - lower) * random_uniform(random) + lower;
}

/**
 * @brief Generate a random number from a Gaussian distribution.
 *
 * Generates a random number from a normal distribution with mean `mu_` and
 * standard deviation `sigma`. The Box-Muller transform is used to generate the
 * random number. Technically this generates two normal distributes random
 * numbers, but we use only one.
 *
 * @param random Random struct
 * @param mu_ Distribution mean
 * @param sigma Distribution standard deviation
 * @return double Number in the interval (-inf, inf)
 */
double random_gauss(Random *random, double mu_, double sigma)
{
    return sigma * sqrt(-2.0 * log(random_uniform(random))) * cos(random_uniform(random) * M_PI * 2) + mu_;
}

#endif // CSYNTH_RANDOM_H
