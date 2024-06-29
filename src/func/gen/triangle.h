//
// triangle.h - A triangle function
//
// `triangle(frequency)` returns a triangle wave with the given frequency.
//
#ifndef CSYNTH_TRIANGLE_H
#define CSYNTH_TRIANGLE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "./const.h"

typedef struct
{
    double last;
    double direction;
} TriangleContext;

static double triangle_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    TriangleContext *context = (TriangleContext *)context_;
    double output = context->last;
    context->last += context->direction * gen_eval(args[0], eval);
    if (context->last > 1.0)
    {
        context->last = 2.0 - context->last;
        context->direction = -context->direction;
    }
    else if (context->last < -1.0)
    {
        context->last = -2.0 - context->last;
        context->direction = -context->direction;
    }
    return output;
}

Func *triangle_osc(Func *tick)
{
    TriangleContext initial = {
        .direction = 4.0,
    };
    return func_create(NULL, triangle_eval, NULL, sizeof(TriangleContext), &initial, FuncFlagNone, FUNCS(tick));
}

#endif // CSYNTH_TRIANGLE_H
