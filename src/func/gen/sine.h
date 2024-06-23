//
// sine.h - A sine function
//
// `sine(frequency)` returns a sine wave with the given frequency.
//
#ifndef CSYNTH_SINE_H
#define CSYNTH_SINE_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "./const.h"

typedef struct
{
    double phase;
    double frequency;
} SineContext;

static double sine_eval(__U int count, Gen **args, double delta, void *context_)
{
    SineContext *context = (SineContext *)context_;
    double frequency = gen_eval(args[0]);
    double step = M_PI * 2 * frequency * delta;
    if (frequency > FUNC_EPSILON)
    {
        context->phase *= context->frequency / frequency;
    }
    double output = sin(context->phase);
    context->phase = fmod(context->phase + step, M_PI * 2);
    context->frequency = frequency;
    return output;
}

Func *sine(Func *frequency)
{
    return func_create(NULL, sine_eval, NULL, sizeof(SineContext), NULL, FUNC_FLAG_DEFAULT, 1, frequency);
}

Func *sine_(double frequency) { return sine(const_(frequency)); }

#endif // CSYNTH_SINE_H
