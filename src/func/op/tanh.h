//
// tanh.h - tanh function
//
#ifndef CSYNTH_TANH_H
#define CSYNTH_TANH_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double output;
} TanhContext;

static double tanh_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    TanhContext *context = (TanhContext *)context_;
    double input = gen_eval(args[0], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->output = tanh(input);
    }
    return context->output;
}

Func *tanh_create(Func *input)
{
    return func_create(NULL, tanh_eval, NULL, sizeof(TanhContext), NULL, FuncFlagNone, input);
}

#endif // CSYNTH_TANH_H
