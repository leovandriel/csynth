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

typedef struct
{
    double time;
} DelayContext;

static double delay_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    DelayContext *context = (DelayContext *)context_;
    double tick = gen_eval(args[0], eval);
    double output = 0.0;
    while (context->time >= 1)
    {
        output = gen_eval(args[1], eval);
        context->time -= tick;
    }
    context->time += tick;
    return output;
}

Func *delay_create(Func *tick, Func *input)
{
    return func_create(NULL, delay_eval, NULL, sizeof(DelayContext), NULL, FuncFlagNone, ARGS(tick, input));
}

#endif // CSYNTH_DELAY_H
