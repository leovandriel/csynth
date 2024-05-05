//
// resonant.h - Second-order second-order IIR filter
//
// `resonant(input, frequency, q_factor)`
//
#ifndef CSYNTH_RESONANT_H
#define CSYNTH_RESONANT_H

#include "../../util/math.h"
#include "../../core/func.h"
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
    double omega = PI_M_2 * frequency * delta;
    double alpha = sin_lookup(omega) / (2.0 * q_factor);
    double a0 = 1.0 + alpha;
    double a1 = -2.0 * sin_lookup(omega + M_PI_2);
    double a2 = 1.0 - alpha;
    double b1 = 2.0 * (1.0 - sin_lookup(omega + M_PI_2));
    double b2 = 1.0 - alpha;
    double output = (a0 * input + a1 * context->x1 + a2 * context->x2 - b1 * context->y1 - b2 * context->y2) / a0;
    context->x2 = context->x1;
    context->x1 = input;
    context->y2 = context->y1;
    context->y1 = output;
    return output;
}

Func *resonant(Func *input, Func *frequency, Func *q_factor)
{
    return func_create(NULL, resonant_eval, NULL, sizeof(ResonantContext), NULL, 3, input, frequency, q_factor);
}

Func *resonant_(Func *input, double frequency, double q_factor) { return resonant(input, const_(frequency), const_(q_factor)); }

#endif // CSYNTH_RESONANT_H
