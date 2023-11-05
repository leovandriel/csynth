//
// step.h - A step function
//
// `step(at)` returns 1 if time is past at, otherwise 0.
//
#ifndef COMPOSER_STEP_H
#define COMPOSER_STEP_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double time;
} StepContext;

double step_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    StepContext *context = (StepContext *)_context;
    double edge = gen_eval(args[0]);
    double value = context->time < edge ? 0.0 : 1.0;
    context->time += delta;
    return value;
}

Func *step(Func *edge)
{
    return func_create(NULL, step_eval, NULL, sizeof(StepContext), NULL, 1, edge);
}

#endif // COMPOSER_STEP_H
