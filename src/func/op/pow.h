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

static double pow_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double a = gen_eval(args[0]);
    double b = gen_eval(args[1]);
    return pow(a, b);
}

Func *pow_op(Func *a, Func *b)
{
    return func_create(NULL, pow_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 2, a, b);
}

Func *pow_op_(Func *input, double exponent) { return pow_op(input, const_(exponent)); }

#endif // CSYNTH_POW_H
