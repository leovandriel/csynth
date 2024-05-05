//
// sine.h - A sine function
//
// `sine(frequency)` returns a sine wave with the given frequency.
//
#ifndef CSYNTH_SINE_H
#define CSYNTH_SINE_H

#include "../../util/math.h"
#include "../../core/func.h"
#include "./const.h"

typedef struct
{
    double phase;
    double frequency;
} SineContext;

static double sine_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    SineContext *context = (SineContext *)context_;
    double frequency = gen_eval(args[0]);
    double step = PI_M_2 * frequency * delta;
    if (frequency > EPSILON)
    {
        context->phase *= context->frequency / frequency;
    }
    double output = sin_lookup(context->phase);
    context->phase = fmod(context->phase + step, PI_M_2);
    context->frequency = frequency;
    return output;
}

Func *sine(Func *frequency)
{
    return func_create(NULL, sine_eval, NULL, sizeof(SineContext), NULL, 1, frequency);
}

Func *sine_(double frequency) { return sine(const_(frequency)); }

#endif // CSYNTH_SINE_H
