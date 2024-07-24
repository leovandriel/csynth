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
    double angle = gen_eval(args[0], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->output = sin(angle);
    }
    return context->output;
}

/**
 * @brief Create a function for the sine function.
 *
 * Due to cost of `sin`, the result is cached in the context and recomputed
 * periodically. Cannot be used to generate a sine wave.
 *
 * @param angle Angle in radians.
 * @return Func* Function object.
 */
Func *sin_create(Func *angle)
{
    return func_create(NULL, sin_eval, NULL, sizeof(SinContext), NULL, FuncFlagNone, angle);
}

#endif // CSYNTH_SIN_H
