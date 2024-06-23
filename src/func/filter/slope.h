//
// slope.h - Limit the slope of a function
//
#ifndef CSYNTH_SLOPE_H
#define CSYNTH_SLOPE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

typedef struct
{
    double last;
} SlopeContext;

static double slope_eval(__U int count, Gen **args, double delta, void *context_)
{
    SlopeContext *context = (SlopeContext *)context_;
    double input = gen_eval(args[0]);
    double slope = gen_eval(args[1]) * delta;
    double diff = input - context->last;
    if (diff > slope)
    {
        diff = slope;
    }
    else if (diff < -slope)
    {
        diff = -slope;
    }
    double output = context->last + diff;
    context->last = output;
    return output;
}

Func *slope(Func *input, Func *frequency)
{
    return func_create(NULL, slope_eval, NULL, sizeof(SlopeContext), NULL, FuncFlagNone, 2, input, frequency);
}

Func *slope_(Func *input, double derivative) { return slope(input, const_(derivative)); }

#endif // CSYNTH_SLOPE_H
