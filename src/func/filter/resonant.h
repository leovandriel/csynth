//
// resonant.h - Second-order second-order IIR filter
//
// `resonant(input, frequency, q_factor)`
//
#ifndef CSYNTH_RESONANT_H
#define CSYNTH_RESONANT_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double va0, va1, va2, vb1, vb2;
    double x1, x2, y1, y2;
} ResonantContext;

static double resonant_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ResonantContext *context = (ResonantContext *)context_;
    double tick = gen_eval(args[0], eval);
    double q_factor = gen_eval(args[1], eval);
    double input = gen_eval(args[2], eval);
    if (eval == NULL || eval->compute_flag)
    {
        double omega = M_PI * 2 * tick;
        double alpha = sin(omega) / (2.0 * q_factor);
        context->va0 = 1.0 + alpha;
        context->va1 = -2.0 * sin(omega + M_PI_2);
        context->va2 = 1.0 - alpha;
        context->vb1 = 2.0 * (1.0 - sin(omega + M_PI_2));
        context->vb2 = 1.0 - alpha;
    }
    double output = (context->va0 * input + context->va1 * context->x1 + context->va2 * context->x2 - context->vb1 * context->y1 - context->vb2 * context->y2) / context->va0;
    context->x2 = context->x1;
    context->x1 = input;
    context->y2 = context->y1;
    context->y1 = output;
    return output;
}

Func *resonant_create(Func *tick, Func *q_factor, Func *input)
{
    return func_create(NULL, resonant_eval, NULL, sizeof(ResonantContext), NULL, FuncFlagNone, tick, q_factor, input);
}

#endif // CSYNTH_RESONANT_H
