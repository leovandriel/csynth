//
// smooth.h - A smooth step function
//
// `smooth(edge0, edge1)` returns 1 if time is past edge1, 0 before edge0.
//
#ifndef CSYNTH_SMOOTH_H
#define CSYNTH_SMOOTH_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double smooth_eval(__U int count, Gen **args, Eval eval, __U void *context_)
{
    double edge0 = gen_eval(args[0], eval);
    double edge1 = gen_eval(args[1], eval);
    double input = gen_eval(args[2], eval);
    if (input <= edge0)
    {
        return 0.0;
    }
    if (input >= edge1)
    {
        return 1.0;
    }
    double ratio = (input - edge0) / (edge1 - edge0);
    return ratio * ratio * (3.0 - 2.0 * ratio);
}

Func *smooth_create(Func *edge0, Func *edge1, Func *input)
{
    return func_create(NULL, smooth_eval, NULL, 0, NULL, FuncFlagNone, FUNCS(edge0, edge1, input));
}

#endif // CSYNTH_SMOOTH_H
