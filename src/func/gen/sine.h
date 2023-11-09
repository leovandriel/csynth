//
// sine.h - A sine function
//
// `sine(frequency)` returns a sine wave with the given frequency.
//
#ifndef CSYNTH_SINE_H
#define CSYNTH_SINE_H

#include <math.h>

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"
#include "../gen/timer.h"

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
    double sign = (fmod(fabs(phase), M_PI * 2) < M_PI) ^ (phase < 0) ? 1 : -1;
    phase = fmod(fabs(phase), M_PI);
    phase = phase > M_PI_2 ? M_PI - phase : phase;
    double offset = phase * sin_table_size / M_PI_2;
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

typedef struct
{
    double phase;
    double frequency;
} SineContext;

static double sine_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    SineContext *context = (SineContext *)context_;
    double frequency = gen_eval(args[0]);
    double step = 2.0 * M_PI * frequency * delta;
    if (frequency > EPSILON)
    {
        context->phase *= context->frequency / frequency;
    }
    double output = sin_lookup(context->phase);
    context->phase = fmod(context->phase + step, M_PI * 2);
    context->frequency = frequency;
    return output;
}

Func *sine(Func *frequency)
{
    return func_create(NULL, sine_eval, NULL, sizeof(SineContext), NULL, 1, frequency);
}

Func *sine_(double frequency) { return sine(const_(frequency)); }

void test_sine_const()
{
    Func *t = sine(const_(1));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 0.5877852419187400);
    assert_gen_equal(g, 0.9510565051057910);
    assert_gen_equal(g, 0.9510565051057910);
    assert_gen_equal(g, 0.5877852419187400);
    assert_gen_equal(g, -0.0000000000000000);
    assert_gen_equal(g, -0.5877852419187400);
    assert_gen_equal(g, -0.9510565051057910);
    assert_gen_equal(g, -0.9510565051057910);
    assert_gen_equal(g, -0.5877852419187400);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 0.5877852419187400);
}

void test_sine_timer()
{
    Func *t = sine(timer());
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 0.0314107589087103);
    assert_gen_equal(g, 0.1045284627888829);
    assert_gen_equal(g, 0.2181432374437673);
    assert_gen_equal(g, 0.3681245516448899);
    assert_gen_equal(g, 0.5446390303877368);
    assert_gen_equal(g, 0.7289686234765415);
    assert_gen_equal(g, 0.8910065137048342);
    assert_gen_equal(g, 0.9892723178837863);
    assert_gen_equal(g, 0.9759167442563212);
    assert_gen_equal(g, 0.8090169800974962);
}

void test_sine_table()
{
    for (double x = -2; x < 2; x += .1)
    {
        double phase = x * M_PI * 2;
        assert_double_range(sin_lookup(phase), sin(phase) + -1e-7, sin(phase) + 1e-7);
    }
}

void test_sine()
{
    test_sine_const();
    test_sine_timer();
    test_sine_table();
}

#endif // CSYNTH_SINE_H
