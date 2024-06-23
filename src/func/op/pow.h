//
// pow.h - Pow function
//
// `pow_op(a, b)` returns a ** b.
//
#ifndef CSYNTH_POW_H
#define CSYNTH_POW_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double pow_eval(__U int count, Gen **args, Eval eval, __U void *context)
{
    double base = gen_eval(args[0], eval);
    double exponent = gen_eval(args[1], eval);
    return pow(base, exponent);
}

Func *pow_op(Func *base, Func *exponent)
{
    return func_create(NULL, pow_eval, NULL, 0, NULL, FuncFlagNone, 2, base, exponent);
}

Func *pow_op_(Func *input, double exponent) { return pow_op(input, const_(exponent)); }

#endif // CSYNTH_POW_H
