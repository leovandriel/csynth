//
// saw.h - A sawtooth function
//
// `saw(frequency)` returns a sawtooth wave with the given frequency.
//
#ifndef CSYNTH_SAW_H
#define CSYNTH_SAW_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double output;
} SawContext;

static double saw_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SawContext *context = (SawContext *)context_;
    double output = context->output;
    double tick = gen_eval(args[0], eval);
    context->output += 2.0 * tick;
    if (context->output > 1.0)
    {
        context->output -= 2.0;
    }
    return output;
}

Func *saw_create(Func *tick)
{
    return func_create(NULL, saw_eval, NULL, sizeof(SawContext), NULL, FuncFlagNone, tick);
}

#endif // CSYNTH_SAW_H
