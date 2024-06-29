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

static double saw_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    SawContext *context = (SawContext *)context_;
    double output = context->output;
    context->output += 2.0 * eval.step[EvalStepAudio];
    if (context->output > 1.0)
    {
        context->output -= 2.0;
    }
    return output;
}

Func *saw_osc()
{
    return func_create(NULL, saw_eval, NULL, sizeof(SawContext), NULL, FuncFlagNone, FUNCS());
}

#endif // CSYNTH_SAW_H
