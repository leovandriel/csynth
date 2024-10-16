#ifndef CSYNTH_SUM_H
#define CSYNTH_SUM_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see sum_create */
typedef struct
{
    /** @brief Accumulated sum. */
    double sum;
} SumContext;

static double sum_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    SumContext *context = (SumContext *)context_;
    double output = context->sum;
    context->sum += gen_eval(args[0], eval);
    return output;
}

/**
 * @brief Create a function that accumulates the sum over time, across samples.
 *
 * @param input Input function.
 * @return Func* Sum function.
 */
Func *sum_create(Func *input)
{
    return func_create(NULL, sum_eval, NULL, NULL, sizeof(SumContext), NULL, FuncFlagNone, input);
}

#endif // CSYNTH_SUM_H
