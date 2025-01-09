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
 * This function creates a generator that maintains a running sum of its input
 * values over time. For each sample, it adds the current input value to the
 * accumulated sum and outputs the previous accumulated value. The sum starts at
 * 0.0 and grows or shrinks based on the input values.
 *
 * Common applications include:
 * - Calculating cumulative changes over time
 * - Creating linear ramps and slopes
 * - Implementing integration in signal processing
 * - Building additive accumulation chains
 *
 * The output behavior depends on the input values:
 * - Positive input values cause linear growth
 * - Negative input values cause linear decay
 * - Zero input maintains constant output
 * - Large input values can cause rapid accumulation
 *
 * @param input Function whose output values will be accumulated into the
 *              running sum over time.
 * @return Func* Sum function that outputs the accumulated total.
 */
Func *sum_create(Func *input)
{
    return func_create(NULL, sum_eval, NULL, NULL, sizeof(SumContext), NULL, FuncFlagNone, input);
}

#endif // CSYNTH_SUM_H
