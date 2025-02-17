#ifndef CSYNTH_MATH_H
#define CSYNTH_MATH_H

#include <stdint.h>

double math_sqrt_0to1(double base)
{
    union
    {
        double d;
        uint64_t u;
    } cast;
    cast.d = base;
    cast.u = (cast.u >> 1) + (1ULL << 61);
    double result = cast.d;
    return (6.0 / 13.0) * (result + base / result);
}

double math_pow_int(double base, int exp)
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
