#ifndef CSYNTH_FOURIER_H
#define CSYNTH_FOURIER_H

#include <complex.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "./math.h"

#define DB_RANGE 80.0

bool fourier_is_power_of_two(size_t value)
{
    return value != 0 && (value & (value - 1)) == 0;
}

double fourier_value_to_db(double value)
{
    return 20.0 * log10(value > DBL_MIN ? value : DBL_MIN);
}

double fourier_db_to_value(double value)
{
    return pow(10.0, value / 20.0);
}

void fourier_fft(complex double *samples, size_t count, bool inverse)
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
    fourier_fft(even, half, inverse);
    fourier_fft(odd, half, inverse);
    double sign = inverse ? 1.0 : -1.0;
    double angle_base = sign * 2.0 * M_PI / (double)count;
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

void fourier_transform(double *in_buffer, size_t in_size, size_t in_offset, double *out_buffer)
{
    complex double fft_buffer[in_size];
    for (size_t i = 0; i < in_size; i++)
    {
        double hanning = (0.5 - 0.5 * cos(2.0 * M_PI * (double)i / (double)in_size));
        fft_buffer[i] = in_buffer[(in_offset + i) % in_size] * hanning;
    }
    fourier_fft(fft_buffer, in_size, false);
    for (size_t j = 0; j < in_size / 2; j++)
    {
        out_buffer[j] = cabs(fft_buffer[j]) / (double)in_size;
    }
}

uint32_t fourier_value_to_color(double value)
{
    double scaled = (double)0x100 * (fourier_value_to_db(value) + DB_RANGE) / DB_RANGE;
    uint32_t clamped = (uint32_t)math_clamp(scaled, 0.0, (double)0xFF);
    return 0xFF000000 | (clamped << 16) | (clamped << 8) | clamped;
}

double fourier_color_to_value(uint32_t color)
{
    return fourier_db_to_value((double)(color & 0xFF) / (double)0x100 * DB_RANGE - DB_RANGE);
}

void fourier_to_rgb(double *in_buffer, size_t in_offset, uint32_t *out_buffer, size_t out_pitch, size_t width, size_t height)
{
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            out_buffer[j * out_pitch + i] = fourier_value_to_color(in_buffer[((i + in_offset) % width + 1) * height - j - 1]);
        }
    }
}

#endif // CSYNTH_FOURIER_H
