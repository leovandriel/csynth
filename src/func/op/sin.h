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

static double sin_eval(__U size_t count, Gen **args, Eval *eval, __U void *context)
{
    double input = gen_eval(args[0], eval);
    return sin(input);
}

Func *sin_create(Func *input)
{
    return func_create(NULL, sin_eval, NULL, 0, NULL, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_SIN_H
