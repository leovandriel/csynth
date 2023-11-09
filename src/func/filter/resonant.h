//
// resonant.h - Second-order second-order IIR filter
//
// `resonant(input, frequency, q_factor)`
//
#ifndef CSYNTH_RESONANT_H
#define CSYNTH_RESONANT_H

#include <math.h>

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"
#include "../gen/sine.h"
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

void test_resonant()
{
    Func *t = resonant(square_(1), const_(2), const_(1));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 1.0000000000000000);
    assert_gen_equal(g, -0.3554467673117652);
    assert_gen_equal(g, 0.9140520505530968);
    assert_gen_equal(g, 0.2068404533398542);
    assert_gen_equal(g, 0.4179689975257589);
    assert_gen_equal(g, -1.5283959545087757);
    assert_gen_equal(g, 1.0572185352198431);
    assert_gen_equal(g, -1.3835083183028376);
    assert_gen_equal(g, -0.0165945916944115);
    assert_gen_equal(g, -0.4292847868595755);
    assert_gen_equal(g, 1.4713719408891881);
    assert_gen_equal(g, -0.9997882144373600);
}

#endif // CSYNTH_RESONANT_H
