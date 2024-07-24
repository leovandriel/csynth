#ifndef CSYNTH_POW_H
#define CSYNTH_POW_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
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
 * Due to cost of `pow`, the result is cached in the context and recomputed
 * periodically.
 *
 * @param base Base value.
 * @param exponent Exponent value.
 * @return Func* Function object.
 */
Func *pow_create(Func *base, Func *exponent)
{
    return func_create(NULL, pow_eval, NULL, sizeof(PowContext), NULL, FuncFlagNone, base, exponent);
}

#endif // CSYNTH_POW_H
