//
// rand.h - A xorshift random number generator
//
#ifndef CSYNTH_TIME_H
#define CSYNTH_TIME_H

#include <time.h>

double time_wall()
{
    struct timespec spec;
    timespec_get(&spec, TIME_UTC);
    return (double)spec.tv_sec + (double)spec.tv_nsec / 1e9;
}

#endif // CSYNTH_TIME_H
