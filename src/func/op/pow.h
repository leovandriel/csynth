#ifndef CSYNTH_POW_H
#define CSYNTH_POW_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see pow_create */
typedef struct
{
    /** @brief Cached output value. */
    double output;
} PowContext;

static double pow_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    PowContext *context = (PowContext *)context_;
    double base = gen_eval(args[0], eval);
    double exponent = gen_eval(args[1], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->output = pow(base, exponent);
    }
    return context->output;
}

/**
 * @brief Create a function for the power function, i.e. base ^ exponent.
 *
 * This function creates a generator that raises a base value to an exponent,
 * computing base^exponent. Due to the computational cost of the pow() function,
 * the result is cached in the context and only recomputed when the compute_flag
 * is set in the evaluator.
 *
 * Common applications include:
 * - Creating exponential curves and envelopes
 * - Implementing waveshapers and distortion effects
 * - Computing frequency ratios for musical intervals
 * - Building amplitude scaling functions
 *
 * The output range depends on the input ranges:
 * - For positive base values, output will be positive
 * - For negative base values, output may be complex (undefined)
 * - Larger exponents can cause very large or small outputs
 * - Base 0 with negative exponent is undefined
 *
 * @param base Base function whose output will be raised to the exponent. Should
 *             generally be non-negative for predictable results.
 * @param exponent Function whose output determines the power to raise the base
 *                to. Integer values are most common but any real value is
 *                valid.
 * @return Func* Power function that outputs base^exponent for each sample.
 */
Func *pow_create(Func *base, Func *exponent)
{
    return func_create(NULL, pow_eval, NULL, NULL, sizeof(PowContext), NULL, FuncFlagNone, base, exponent);
}

#endif // CSYNTH_POW_H
