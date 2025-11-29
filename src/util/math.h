#ifndef CSYNTH_MATH_H
#define CSYNTH_MATH_H

#include <complex.h>
#include <stddef.h>
#include <stdint.h>

#define PI 3.14159265358979323846264338327950288

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
    if (base == 0.0)
    {
        return 0.0;
    }
    if (exp < 0)
    {
        base = 1.0 / base;
        exp = -exp;
    }
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

double math_gamma(double value, int gamma)
{
    return 1 - math_pow_int(1 - value, gamma);
}

double math_clamp(double value, double min, double max)
{
    return value <= max ? (value >= min ? value : min) : max;
}

#endif // CSYNTH_MATH_H
