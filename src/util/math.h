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

void math_fft(complex double *samples, size_t window)
{
    if (window <= 1)
    {
        return;
    }
    complex double even[window / 2], odd[window / 2];
    for (size_t i = 0; i < window / 2; i++)
    {
        even[i] = samples[i * 2];
        odd[i] = samples[i * 2 + 1];
    }
    math_fft(even, window / 2);
    math_fft(odd, window / 2);
    for (size_t k = 0; k < window / 2; k++)
    {
        complex double twiddle = cexp(-2.0 * I * PI * (double)k / (double)window) * odd[k];
        samples[k] = even[k] + twiddle;
        samples[k + window / 2] = even[k] - twiddle;
    }
}

double math_gamma(double value, int gamma)
{
    return 1 - math_pow_int(1 - value, gamma);
}

#endif // CSYNTH_MATH_H
