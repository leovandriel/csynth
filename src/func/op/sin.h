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

static double sin_eval(__U int count, Gen **args, __U double delta, __U void *context)
{
    double input = gen_eval(args[0]);
    return sin(input);
}

Func *sin_op(Func *input)
{
    return func_create(NULL, sin_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 1, input);
}

#endif // CSYNTH_SIN_H
