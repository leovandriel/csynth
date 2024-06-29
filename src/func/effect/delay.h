//
// delay.h - A time delay on the sampling of a function
//
// `delay(input, duration)` waits duration (a function) seconds before it starts
// sampling the input function.
//
#ifndef CSYNTH_DELAY_H
#define CSYNTH_DELAY_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"
#include "../op/neg.h"

typedef struct
{
    double time;
} DelayContext;

static double delay_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    DelayContext *context = (DelayContext *)context_;
    double span = gen_eval(args[1], eval);
    double output = 0.0;
    while (context->time >= span)
    {
        output = gen_eval(args[0], eval);
        context->time -= eval.tick[EvalTickPitch];
    }
    context->time += eval.tick[EvalTickPitch];
    return output;
}

Func *delay(Func *input, Func *duration)
{
    return func_create(NULL, delay_eval, NULL, sizeof(DelayContext), NULL, FuncFlagNone, FUNCS(input, duration));
}

Func *delay_(Func *input, double duration) { return delay(input, const_(duration)); }

#endif // CSYNTH_DELAY_H
