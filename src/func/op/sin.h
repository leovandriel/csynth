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

typedef struct
{
    double output;
} SinContext;

static double sin_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    SinContext *context = (SinContext *)context_;
    double input = gen_eval(args[0], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->output = sin(input);
    }
    return context->output;
}

Func *sin_create(Func *input)
{
    return func_create(NULL, sin_eval, NULL, sizeof(SinContext), NULL, FuncFlagNone, input);
}

#endif // CSYNTH_SIN_H
