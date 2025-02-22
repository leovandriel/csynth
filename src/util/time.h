#ifndef CSYNTH_TIME_H
#define CSYNTH_TIME_H

#include <time.h>

double time_sec(void)
{
    struct timespec spec;
    timespec_get(&spec, TIME_UTC);
    return (double)spec.tv_sec + (double)spec.tv_nsec * 1e-9;
}

void time_sleep(double seconds)
{
    double whole = (int)seconds;
    double frac = seconds - whole;
    struct timespec req = {whole, frac * 1e9};
    nanosleep(&req, NULL);
}

#endif // CSYNTH_TIME_H
