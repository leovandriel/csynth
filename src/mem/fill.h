//
// fill.h - Buffer filling functions
//
#ifndef CSYNTH_FILL_H
#define CSYNTH_FILL_H

#include "../util/rand.h"

double fill_rand_0_1(__attribute__((unused)) size_t index, void *context)
{
    Random *random = (Random *)context;
    return random_range(random, 0, 1);
}

double fill_rand_1_1(__attribute__((unused)) size_t index, void *context)
{
    Random *random = (Random *)context;
    return random_range(random, -1, 1);
}

double fill_inc(size_t index, __attribute__((unused)) void *context)
{
    return (double)index;
}

#endif // CSYNTH_FILL_H
