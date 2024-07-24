#ifndef CSYNTH_SINE_H
#define CSYNTH_SINE_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

#define SINE_TABLE_SIZE (1 << 11) // 2048, which at 44100 Hz sample is accurate down to 20 Hz

typedef struct
{
    double data[SINE_TABLE_SIZE];
    bool initialized;
} SineTable;

SineTable sine_table = {0};

static csError sine_table_init()
{
    for (unsigned long i = 0; i < SINE_TABLE_SIZE; i++)
    {
        sine_table.data[i] = sin(M_PI_2 * (double)i / (double)SINE_TABLE_SIZE);
    }
    return csErrorNone;
}

static csError sine_table_ensure()
{
    if (!sine_table.initialized)
    {
        return sine_table_init();
    }
    return csErrorNone;
}

static double sine_table_lookup(double phase)
{
    double sign = phase < 0.5 ? 1 : -1;
    phase = fmod(phase, 0.5);
    phase = phase > 0.25 ? 0.5 - phase : phase;
    double offset = phase * (double)(SINE_TABLE_SIZE * 4);
    unsigned long lower = floor(offset);
    if (lower < SINE_TABLE_SIZE - 1)
    {
        // TODO(leo): higher-order interpolation
        double rem = offset - (double)lower;
        return sign * (sine_table.data[lower] * (1 - rem) + sine_table.data[lower + 1] * rem);
    }
    return sign * sine_table.data[lower];
}

typedef struct
{
    double phase;
} SineContext;

static double sine_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SineContext *context = (SineContext *)context_;
    double output = sine_table_lookup(context->phase);
    double tick = gen_eval(args[0], eval);
    context->phase = fmod(context->phase + tick, 1.0);
    return output;
}

static bool sine_init(__U size_t count, __U Gen **args, __U void *context_)
{
    sine_table_ensure();
    return false;
}

/**
 * @brief Create a function that outputs an approximate sine wave.
 *
 * Due to the cost of `sin`, the result is cached in a lookup table and
 * interpolated.
 *
 * @param tick Func* Periods per sample.
 * @return Func* Function object.
 */
Func *sine_create(Func *tick)
{
    return func_create(sine_init, sine_eval, NULL, sizeof(SineContext), NULL, FuncFlagNone, tick);
}

#endif // CSYNTH_SINE_H
