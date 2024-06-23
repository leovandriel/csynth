//
// saw.h - A sawtooth function
//
// `saw(frequency)` returns a sawtooth wave with the given frequency.
//
#ifndef CSYNTH_SAW_H
#define CSYNTH_SAW_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "./const.h"

typedef struct
{
    double output;
} SawContext;

static double saw_eval(__U int count, Gen **args, double delta, void *context_)
{
    SawContext *context = (SawContext *)context_;
    double frequency = gen_eval(args[0]);
    double output = context->output;
    context->output += 2.0 * frequency * delta;
    if (context->output > 1.0)
    {
        context->output -= 2.0;
    }
    return output;
}

Func *saw(Func *frequency)
{
    return func_create(NULL, saw_eval, NULL, sizeof(SawContext), NULL, FUNC_FLAG_DEFAULT, 1, frequency);
}

Func *saw_(double frequency) { return saw(const_(frequency)); }

#endif // CSYNTH_SAW_H
