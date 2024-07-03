//
// loop.h - A time loop on the sampling of a function
//
// `loop(input, duration)` loops the input function every duration (a function).
//
#ifndef CSYNTH_LOOP_H
#define CSYNTH_LOOP_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double time;
} LoopContext;

static double loop_eval(__U int count, Gen **args, Eval *eval, void *context_)
{
    LoopContext *context = (LoopContext *)context_;
    if (context->time >= 1)
    {
        context->time -= 1;
        gen_reset(args[1]);
    }
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    context->time += tick;
    return input;
}

Func *loop_create(Func *tick, Func *input)
{
    return func_create(NULL, loop_eval, NULL, sizeof(LoopContext), NULL, FuncFlagNone, FUNCS(tick, input));
}

#endif // CSYNTH_LOOP_H
