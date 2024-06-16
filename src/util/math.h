//
// math.h
//
#ifndef CSYNTH_MATH_H
#define CSYNTH_MATH_H

#include <math.h>

#include "../mem/alloc.h"
#include "../util/error.h"

static const double PI_M_2 = M_PI * 2;

static double *sin_table = NULL;
static unsigned long sin_table_size = 1 << 12;

static csError sin_table_ensure()
{
    if (sin_table == NULL)
    {
        sin_table = (double *)malloc_(sizeof(double) * sin_table_size);
        if (sin_table == NULL)
        {
            return error_type(csErrorMemoryAlloc);
        }
        for (unsigned long i = 0; i < sin_table_size; i++)
        {
            sin_table[i] = sin(M_PI_2 * (double)i / (double)sin_table_size);
        }
    }
    return csErrorNone;
}

void sin_table_free()
{
    free_(sin_table);
    sin_table = NULL;
}

double sin_lookup(double phase)
{
    if (sin_table_ensure() != csErrorNone)
    {
        return 0;
    }
    double sign = phase < 0 ? -1 : 1;
    phase = phase < 0 ? -phase * M_2_PI : phase * M_2_PI;
    sign = (unsigned long)phase % 4 < 2 ? sign : -sign;
    phase = fmod(phase, 2);
    phase = phase > 1 ? 2 - phase : phase;
    double offset = phase * (double)sin_table_size;
    unsigned long lower = floor(offset);
    if (lower < sin_table_size - 1)
    {
        // TODO(leo): higher-order interpolation
        double rem = offset - (double)lower;
        return sign * (sin_table[lower] * (1 - rem) + sin_table[lower + 1] * rem);
    }
    return sign * sin_table[lower];
}

#endif // CSYNTH_MATH_H
