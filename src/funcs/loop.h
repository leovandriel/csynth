#ifndef COMPOSER_LOOP_H
#define COMPOSER_LOOP_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double time;
} LoopContext;

double loop_eval(Func **args, __attribute__((unused)) int count, double delta, void *_context)
{
    LoopContext *context = (LoopContext *)_context;
    double duration = func_eval(args[1]);
    if (context->time >= duration)
    {
        context->time -= duration;
        func_init(args[0], delta);
    }
    double output = func_eval(args[0]);
    context->time += delta;
    return output;
}

Func *loop(Func *input, Func *duration)
{
    return func_create(NULL, loop_eval, NULL, sizeof(LoopContext), NULL, 2, input, duration);
}

#endif // COMPOSER_LOOP_H
