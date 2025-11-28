#include "../../src/util/fourier.h"
#include "./test.h"

void test_fourier_fft(void)
{
    complex double samples[4] = {1.0, 2.0, 3.0, 4.0};
    fourier_fft(samples, 4, false);
    assert_complex_equal(samples[0], 10.0);
    assert_complex_equal(samples[1], -2.0 + 2.0i);
    assert_complex_equal(samples[2], -2.0);
    assert_complex_equal(samples[3], -2.0 - 2.0i);
}

void test_fourier_fft_inverse(void)
{
    complex double samples[4] = {10.0, -2.0 + 2.0i, -2.0, -2.0 - 2.0i};
    fourier_fft(samples, 4, true);
    assert_complex_equal(samples[0], 1.0);
    assert_complex_equal(samples[1], 2.0);
    assert_complex_equal(samples[2], 3.0);
    assert_complex_equal(samples[3], 4.0);
}

void test_fourier_fft_both(void)
{
    complex double samples[8] = {1.0, -2.0, 3.0, -4.0, 1.0, 2.0, 3.0, 4.0};
    fourier_fft(samples, 8, false);
    fourier_fft(samples, 8, true);
    assert_complex_equal(samples[0], 1.0);
    assert_complex_equal(samples[1], -2.0);
    assert_complex_equal(samples[2], 3.0);
    assert_complex_equal(samples[3], -4.0);
    assert_complex_equal(samples[4], 1.0);
    assert_complex_equal(samples[5], 2.0);
    assert_complex_equal(samples[6], 3.0);
    assert_complex_equal(samples[7], 4.0);
}

void test_fourier(void)
{
    test_fourier_fft();
    test_fourier_fft_inverse();
    test_fourier_fft_both();
}