#ifndef CSYNTH_PROD_H
#define CSYNTH_PROD_H

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see prod_create */
typedef struct
{
    /** @brief Accumulated product. */
    double prod;
} ProdContext;

static double prod_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ProdContext *context = (ProdContext *)context_;
    double output = context->prod;
    context->prod *= gen_eval(args[0], eval);
    return output;
}

/**
 * @brief Create a function that accumulates the product over time, across
 * samples.
 *
 * This function creates a generator that maintains a running product of its
 * input values over time. For each sample, it multiplies the current input
 * value with the accumulated product and outputs the previous accumulated
 * value. The product starts at 1.0 and grows or shrinks based on the input
 * values.
 *
 * Common applications include:
 * - Calculating cumulative gain changes over time
 * - Creating exponential growth or decay effects
 * - Implementing multiplicative accumulation in signal processing
 * - Building complex modulation chains
 *
 * The output behavior depends on the input values:
 * - Input values > 1 cause exponential growth
 * - Input values between 0 and 1 cause decay
 * - Input values < 0 cause sign flipping and scaling
 * - Input
 */
Func *prod_create(Func *input)
{
    ProdContext initial = {.prod = 1.0};
    return func_create(NULL, prod_eval, NULL, NULL, sizeof(ProdContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_PROD_H
