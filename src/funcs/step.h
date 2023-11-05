#ifndef COMPOSER_STEP_H
#define COMPOSER_STEP_H

#include <math.h>

#include "../core/func.h"

typedef struct
{
    double time;
} StepContext;

double step_eval(Func **args, __attribute__((unused)) int count, double delta, void *_context)
{
    StepContext *context = (StepContext *)_context;
    double span = func_eval(args[0]);
    double value = context->time < span ? 0.0 : 1.0;
    context->time += delta;
    return value;
}

Func *step(Func *at)
{
    return func_create(NULL, step_eval, NULL, sizeof(StepContext), NULL, 1, at);
}

#endif // COMPOSER_STEP_H
