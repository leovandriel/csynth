//
// tanh.h - tanh function
//
#ifndef CSYNTH_TANH_H
#define CSYNTH_TANH_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

static double tanh_eval(__U int count, Gen **args, Eval *eval, __U void *context)
{
    double input = gen_eval(args[0], eval);
    return tanh(input);
}

Func *tanh_create(Func *input)
{
    return func_create(NULL, tanh_eval, NULL, 0, NULL, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_TANH_H
