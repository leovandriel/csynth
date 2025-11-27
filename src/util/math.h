#ifndef CSYNTH_MATH_H
#define CSYNTH_MATH_H

#include <complex.h>
#include <stdbool.h>
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

void math_fft(complex double *samples, size_t count, bool inverse)
{
    if (count <= 1)
    {
        return;
    }
    size_t half = count / 2;
    complex double even[half], odd[half];
    for (size_t i = 0; i < half; i++)
    {
        even[i] = samples[2 * i];
        odd[i] = samples[2 * i + 1];
    }
    math_fft(even, half, inverse);
    math_fft(odd, half, inverse);
    double sign = inverse ? 1.0 : -1.0;
    double angle_base = sign * 2.0 * PI / (double)count;
    for (size_t k = 0; k < half; k++)
    {
        complex double twiddle = cexp(I * angle_base * (double)k) * odd[k];
        if (inverse)
        {
            samples[k] = (even[k] + twiddle) / 2.0;
            samples[k + half] = (even[k] - twiddle) / 2.0;
        }
        else
        {
            samples[k] = even[k] + twiddle;
            samples[k + half] = even[k] - twiddle;
        }
    }
}

double math_gamma(double value, int gamma)
{
    return 1 - math_pow_int(1 - value, gamma);
}

#endif // CSYNTH_MATH_H
