//
// fill.h - Buffer filling functions
//
#ifndef CSYNTH_FILL_H
#define CSYNTH_FILL_H

#include "../util/rand.h"

double fill_rand_0_1(__attribute__((unused)) size_t index)
{
    return rand_range(0, 1);
}

double fill_rand_1_1(__attribute__((unused)) size_t index)
{
    return rand_range(-1, 1);
}

double fill_inc(size_t index)
{
    return (double)index;
}

#endif // CSYNTH_FILL_H
