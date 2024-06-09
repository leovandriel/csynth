//
// smooth.h - A smooth step function
//
// `smooth(edge0, edge1)` returns 1 if time is past edge1, 0 before edge0.
//
#ifndef CSYNTH_SMOOTH_H
#define CSYNTH_SMOOTH_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double smooth_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context_)
{
    double input = gen_eval(args[0]);
    double edge0 = gen_eval(args[1]);
    double edge1 = gen_eval(args[2]);
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

Func *smooth_op(Func *input, Func *edge0, Func *edge1)
{
    return func_create(NULL, smooth_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 3, input, edge0, edge1);
}

Func *smooth_op_(Func *input, double edge0, double edge1) { return smooth_op(input, const_(edge0), const_(edge1)); }

#endif // CSYNTH_SMOOTH_H
