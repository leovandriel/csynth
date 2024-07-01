//
// slope.h - Limit the slope of a function
//
#ifndef CSYNTH_SLOPE_H
#define CSYNTH_SLOPE_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double last;
} SlopeContext;

static double slope_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    SlopeContext *context = (SlopeContext *)context_;
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    double diff = input - context->last;
    if (diff > tick)
    {
        diff = tick;
    }
    else if (diff < -tick)
    {
        diff = -tick;
    }
    double output = context->last + diff;
    context->last = output;
    return output;
}

Func *slope_create(Func *tick, Func *input)
{
    return func_create(NULL, slope_eval, NULL, sizeof(SlopeContext), NULL, FuncFlagNone, FUNCS(tick, input));
}

#endif // CSYNTH_SLOPE_H
