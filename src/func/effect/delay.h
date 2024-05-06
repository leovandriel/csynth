//
// delay.h - A time delay on the sampling of a function
//
// `delay(input, duration)` waits duration (a function) seconds before it starts
// sampling the input function.
//
#ifndef CSYNTH_DELAY_H
#define CSYNTH_DELAY_H

#include "../../core/func.h"
#include "../gen/const.h"
#include "../op/neg.h"

typedef struct
{
    double time;
} DelayContext;

static double delay_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    DelayContext *context = (DelayContext *)context_;
    double span = gen_eval(args[1]);
    double output = 0.0;
    while (context->time >= span)
    {
        output = gen_eval(args[0]);
        context->time -= delta;
    }
    context->time += delta;
    return output;
}

Func *delay(Func *input, Func *duration)
{
    return func_create(NULL, delay_eval, NULL, sizeof(DelayContext), NULL, FUNC_FLAG_DEFAULT, 2, input, duration);
}

Func *delay_(Func *input, double frequency) { return delay(input, const_(frequency)); }

#endif // CSYNTH_DELAY_H
