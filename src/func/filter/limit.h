//
// limit.h - Limits the delta between successive samples
//
// `limit(input, limit)` with input and limit functions and limit the amplitude
// delta. This can be used to prevent clicks and pops.
//
// TODO(leo): merge into slope
//
#ifndef CSYNTH_LIMIT_H
#define CSYNTH_LIMIT_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double output;
} LimitContext;

static double limit_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    LimitContext *context = (LimitContext *)context_;
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    if (input < context->output - tick)
    {
        input = context->output - tick;
    }
    else if (input > context->output + tick)
    {
        input = context->output + tick;
    }
    context->output = input;
    return input;
}

Func *limit_create(Func *tick, Func *input)
{
    return func_create(NULL, limit_eval, NULL, sizeof(LimitContext), NULL, FuncFlagNone, FUNCS(tick, input));
}

#endif // CSYNTH_LIMIT_H
