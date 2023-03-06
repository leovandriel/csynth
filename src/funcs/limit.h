#ifndef COMPOSER_LIMIT_H
#define COMPOSER_LIMIT_H

#include "../core/func.h"

typedef struct
{
    double output;
} LimitContext;

double limit_eval(unsigned long index, int rate, Func **args, __attribute__((unused)) int count, void *_context)
{
    LimitContext *context = (LimitContext *)_context;
    double input = func_eval(args[0], index, rate);
    double limit = func_eval(args[1], index, rate) / rate;
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
