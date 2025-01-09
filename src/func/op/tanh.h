#ifndef CSYNTH_TANH_H
#define CSYNTH_TANH_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see tanh_create */
typedef struct
{
    /** @brief Cached output value. */
    double output;
} TanhContext;

static double tanh_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    TanhContext *context = (TanhContext *)context_;
    double angle = gen_eval(args[0], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->output = tanh(angle);
    }
    return context->output;
}

/**
 * @brief Create a function for the hyperbolic tangent function, i.e. tanh(x).
 *
 * This function creates a generator that computes the hyperbolic tangent of its
 * input. Due to the computational cost of the tanh() function, the result is
 * cached in the context and only recomputed when the compute_flag is set in the
 * evaluator.
 *
 * Common applications include:
 * - Soft clipping and saturation effects
 * - Neural network activation functions
 * - Smooth compression of signals
 * - Waveshaping and distortion
 *
 * The output range will always be (-1, 1):
 * - Output approaches +1 asymptotically as input increases
 * - Output approaches -1 asymptotically as input decreases
 * - Linear response near 0 with smooth compression at extremes
 * - Symmetric around origin: tanh(-x) = -tanh(x)
 *
 * @param angle Function whose output provides the input value. The hyperbolic
 *             tangent will be computed for each value.
 * @return Func* Hyperbolic tangent function.
 */
Func *tanh_create(Func *angle)
{
    return func_create(NULL, tanh_eval, NULL, NULL, sizeof(TanhContext), NULL, FuncFlagNone, angle);
}

#endif // CSYNTH_TANH_H
