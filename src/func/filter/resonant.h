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
#include "../gen/const.h"

typedef struct
{
    double x1, x2, y1, y2;
} ResonantContext;

static double resonant_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    ResonantContext *context = (ResonantContext *)context_;
    double input = gen_eval(args[0]);
    double frequency = gen_eval(args[1]);
    double q_factor = gen_eval(args[2]);
    double omega = M_PI * 2 * frequency * delta;
    double alpha = sin(omega) / (2.0 * q_factor);
    double va0 = 1.0 + alpha;
    double va1 = -2.0 * sin(omega + M_PI_2);
    double va2 = 1.0 - alpha;
    double vb1 = 2.0 * (1.0 - sin(omega + M_PI_2));
    double vb2 = 1.0 - alpha;
    double output = (va0 * input + va1 * context->x1 + va2 * context->x2 - vb1 * context->y1 - vb2 * context->y2) / va0;
    context->x2 = context->x1;
    context->x1 = input;
    context->y2 = context->y1;
    context->y1 = output;
    return output;
}

Func *resonant(Func *input, Func *frequency, Func *q_factor)
{
    return func_create(NULL, resonant_eval, NULL, sizeof(ResonantContext), NULL, FUNC_FLAG_DEFAULT, 3, input, frequency, q_factor);
}

Func *resonant_(Func *input, double frequency, double q_factor) { return resonant(input, const_(frequency), const_(q_factor)); }

#endif // CSYNTH_RESONANT_H
