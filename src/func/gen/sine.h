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

typedef struct
{
    double phase;
} SineContext;

static double sine_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    SineContext *context = (SineContext *)context_;
    double output = sin(context->phase * M_PI * 2);
    double tick = gen_eval(args[0], eval);
    context->phase = fmod(context->phase + tick, 1.0);
    return output;
}

Func *sine_gen(Func *tick)
{
    return func_create(NULL, sine_eval, NULL, sizeof(SineContext), NULL, FuncFlagNone, FUNCS(tick));
}

#endif // CSYNTH_SINE_H
