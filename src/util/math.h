#ifndef CSYNTH_MATH_H
#define CSYNTH_MATH_H

#include <stdint.h>

double fast_sqrt_0to1(double x)
{
    union
    {
        double d;
        uint64_t u;
    } cast;
    cast.d = x;
    cast.u = (cast.u >> 1) + (1ULL << 61);
    double y = cast.d;
    return (6.0 / 13.0) * (y + x / y);
}

double fast_pow(double base, int exp)
{
    double result = 1.0;
    while (exp > 0)
    {
        if (exp & 1)
        {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return result;
}

#endif // CSYNTH_MATH_H
