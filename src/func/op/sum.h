//
// sum.h - Sum input values over time.
//
#ifndef CSYNTH_SUM_H
#define CSYNTH_SUM_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double sum;
} SumContext;

static double sum_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SumContext *context = (SumContext *)context_;
    double output = context->sum;
    context->sum += gen_eval(args[0], eval);
    return output;
}

Func *sum_create(Func *input)
{
    return func_create(NULL, sum_eval, NULL, sizeof(SumContext), NULL, FuncFlagNone, ARGS(input));
}

#endif // CSYNTH_SUM_H
