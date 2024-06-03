//
// rand.h - A xorshift random number generator
//
#ifndef CSYNTH_TIME_H
#define CSYNTH_TIME_H

#include <time.h>

double time_wall()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

#endif // CSYNTH_TIME_H
