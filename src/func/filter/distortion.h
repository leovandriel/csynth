//
// distortion.h - A first-order high-pass filter
//
#ifndef CSYNTH_DISTORTION_H
#define CSYNTH_DISTORTION_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double distortion_eval(__U int count, Gen **args, Eval eval, __U void *context_)
{
    double input = gen_eval(args[0], eval);
    double shape = gen_eval(args[1], eval);
    double exp_shape = expm1(shape);
    return (((1 + exp_shape) * input) / (1 + exp_shape * fabs(input)));
}

Func *distortion(Func *input, Func *shape)
{
    return func_create(NULL, distortion_eval, NULL, 0, NULL, FuncFlagNone, 2, input, shape);
}

Func *distortion_(Func *input, double shape) { return distortion(input, const_(shape)); }

#endif // CSYNTH_DISTORTION_H
