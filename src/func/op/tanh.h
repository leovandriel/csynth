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
    double angle = gen_eval(args[0], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->output = tanh(angle);
    }
    return context->output;
}

/**
 * @brief Create a function for the hyperbolic tangent function.
 *
 * Due to cost of `tanh`, the result is cached in the context and recomputed
 * periodically.
 *
 * @param angle Angle in radians.
 * @return Func* Function object.
 */
Func *tanh_create(Func *angle)
{
    return func_create(NULL, tanh_eval, NULL, sizeof(TanhContext), NULL, FuncFlagNone, angle);
}

#endif // CSYNTH_TANH_H
