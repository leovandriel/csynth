#ifndef CSYNTH_DISTORTION_H
#define CSYNTH_DISTORTION_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see distortion_create */
typedef struct
{
    /** @brief Exponential shape factor. */
    double exp_shape;
} DistortionContext;

static double distortion_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    DistortionContext *context = (DistortionContext *)context_;
    double shape = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->exp_shape = expm1(shape);
    }
    return (((1 + context->exp_shape) * input) / (1 + context->exp_shape * fabs(input)));
}

/**
 * @brief Create a function that distorts the input signal.
 *
 * @param shape Exponential shape factor.
 * @param input Input signal.
 * @return Func* Distortion function.
 */
Func *distortion_create(Func *shape, Func *input)
{
    return func_create(NULL, distortion_eval, NULL, NULL, sizeof(DistortionContext), NULL, FuncFlagNone, shape, input);
}

#endif // CSYNTH_DISTORTION_H
