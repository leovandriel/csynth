//
// sin.h - Sin function
//
// `sin_op(a, b)` returns a ** b.
//
#ifndef CSYNTH_SIN_H
#define CSYNTH_SIN_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double sin_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context)
{
    double x = gen_eval(args[0]);
    return sin(x);
}

Func *sin_op(Func *f)
{
    return func_create(NULL, sin_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 1, f);
}

#endif // CSYNTH_SIN_H