//
// math.h
//
#ifndef CSYNTH_MATH_H
#define CSYNTH_MATH_H

#include <stddef.h>
#include <stdlib.h>
#include <math.h>

static const double PI_M_2 = M_PI * 2;

static double *sin_table = NULL;
static unsigned long sin_table_size = 1 << 12;

void ensure_sin_table()
{
    if (sin_table == NULL)
    {
        sin_table = (double *)malloc(sizeof(double) * sin_table_size);
        for (unsigned long i = 0; i < sin_table_size; i++)
        {
            sin_table[i] = sin(M_PI_2 * i / sin_table_size);
        }
    }
}

double sin_lookup(double phase)
{
    ensure_sin_table();
    double sign = phase < 0 ? -1 : 1;
    phase = phase < 0 ? -phase * M_2_PI : phase * M_2_PI;
    sign = (unsigned long)phase % 4 < 2 ? sign : -sign;
    phase = fmod(phase, 2);
    phase = phase > 1 ? 2 - phase : phase;
    double offset = phase * sin_table_size;
    unsigned long lower = floor(offset);
    if (lower < sin_table_size - 1)
    {
        // TODO: higher-order interpolation
        double rem = offset - lower;
        return sign * (sin_table[lower] * (1 - rem) + sin_table[lower + 1] * rem);
    }
    else
    {
        return sign * sin_table[lower];
    }
}

#endif // CSYNTH_MATH_H
