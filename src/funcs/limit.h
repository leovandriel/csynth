#ifndef COMPOSER_LIMIT_H
#define COMPOSER_LIMIT_H

#include "../core/func.h"

typedef struct
{
    double output;
} LimitContext;

double limit_eval(Func **args, __attribute__((unused)) int count, double delta, void *_context)
{
    LimitContext *context = (LimitContext *)_context;
    double input = func_eval(args[0]);
    double limit = func_eval(args[1]) * delta;
    if (input < context->output - limit)
    {
        input = context->output - limit;
    }
    else if (input > context->output + limit)
    {
        input = context->output + limit;
    }
    context->output = input;
    return input;
}

Func *limit(Func *input, Func *limit)
{
    return func_create(NULL, limit_eval, NULL, sizeof(LimitContext), NULL, 2, input, limit);
}

#endif // COMPOSER_LIMIT_H
