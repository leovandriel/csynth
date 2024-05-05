//
// limit.h - Limits the delta between successive samples
//
// `limit(input, limit)` with input and limit functions and limit the amplitude
// delta. This can be used to prevent clicks and pops.
//
#ifndef CSYNTH_LIMIT_H
#define CSYNTH_LIMIT_H

#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double output;
} LimitContext;

static double limit_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    LimitContext *context = (LimitContext *)context_;
    double input = gen_eval(args[0]);
    double diff = gen_eval(args[1]) * delta;
    if (input < context->output - diff)
    {
        input = context->output - diff;
    }
    else if (input > context->output + diff)
    {
        input = context->output + diff;
    }
    context->output = input;
    return input;
}

Func *limit(Func *input, Func *diff)
{
    return func_create(NULL, limit_eval, NULL, sizeof(LimitContext), NULL, FUNC_FLAG_DEFAULT, 2, input, diff);
}

Func *limit_(Func *input, double diff) { return limit(input, const_(diff)); }

#endif // CSYNTH_LIMIT_H
