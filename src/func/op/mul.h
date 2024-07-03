//
// mul.h - Multiplication function
//
// `mul(a, b)` returns the product of a list of functions.
//
#ifndef CSYNTH_MUL_H
#define CSYNTH_MUL_H

#include <stdarg.h>

#include "../../core/func.h"
#include "../../core/gen.h"

static double mul_eval(int count, Gen **args, Eval *eval, __U void *context)
{
    double output = 1.0;
    for (int i = 0; i < count; i++)
    {
        output *= gen_eval(args[i], eval);
    }
    return output;
}

Func *mul_create(int count, Func **args)
{
    return func_create(NULL, mul_eval, NULL, 0, NULL, FuncFlagNone, count, args);
}

#endif // CSYNTH_MUL_H
