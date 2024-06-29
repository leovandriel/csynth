//
// loop.h - A time loop on the sampling of a function
//
// `loop(input, duration)` loops the input function every duration (a function).
//
#ifndef CSYNTH_LOOP_H
#define CSYNTH_LOOP_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

typedef struct
{
    double time;
} LoopContext;

static double loop_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    LoopContext *context = (LoopContext *)context_;
    double duration = gen_eval(args[1], eval);
    if (context->time >= duration)
    {
        context->time -= duration;
        gen_reset(args[0]);
    }
    double output = gen_eval(args[0], eval);
    context->time += eval.step[EvalStepAudio];
    return output;
}

Func *loop(Func *input, Func *duration)
{
    return func_create(NULL, loop_eval, NULL, sizeof(LoopContext), NULL, FuncFlagNone, FUNCS(input, duration));
}

Func *loop_(Func *input, double duration) { return loop(input, const_(duration)); }

#endif // CSYNTH_LOOP_H
