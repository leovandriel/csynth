//
// distortion.h - A first-order high-pass filter
//
#ifndef CSYNTH_DISTORTION_H
#define CSYNTH_DISTORTION_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

static double distortion_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    double shape = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    double exp_shape = expm1(shape);
    return (((1 + exp_shape) * input) / (1 + exp_shape * fabs(input)));
}

Func *distortion_create(Func *shape, Func *input)
{
    return func_create(NULL, distortion_eval, NULL, 0, NULL, FuncFlagNone, ARGS(shape, input));
}

#endif // CSYNTH_DISTORTION_H
