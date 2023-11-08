//
// resonant.h - Second-order second-order IIR filter
//
// `resonant(input, frequency, q_factor)`
//
#ifndef CSYNTH_RESONANT_H
#define CSYNTH_RESONANT_H

#include <assert.h>
#include <math.h>

#include "../../core/func.h"
#include "../gen/const.h"
#include "../gen/square.h"

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
    double omega = 2.0 * M_PI * frequency * delta;
    double alpha = sin(omega) / (2.0 * q_factor);
    double a0 = 1.0 + alpha;
    double a1 = -2.0 * cos(omega);
    double a2 = 1.0 - alpha;
    double b1 = 2.0 * (1.0 - cos(omega));
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

void test_resonant()
{
    Func *t = resonant(square_(1), const_(2), const_(1));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-4;
    assert(fabs(gen_eval(g) - 1.000000) < epsilon);
    assert(fabs(gen_eval(g) - -0.355447) < epsilon);
    assert(fabs(gen_eval(g) - 0.914052) < epsilon);
    assert(fabs(gen_eval(g) - 0.206840) < epsilon);
    assert(fabs(gen_eval(g) - 0.417969) < epsilon);
    assert(fabs(gen_eval(g) - -1.528396) < epsilon);
    assert(fabs(gen_eval(g) - 1.057219) < epsilon);
    assert(fabs(gen_eval(g) - -1.383508) < epsilon);
    assert(fabs(gen_eval(g) - -0.016595) < epsilon);
    assert(fabs(gen_eval(g) - -0.429285) < epsilon);
    assert(fabs(gen_eval(g) - 1.471372) < epsilon);
    assert(fabs(gen_eval(g) - -0.999788) < epsilon);
}

#endif // CSYNTH_RESONANT_H
