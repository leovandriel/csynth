//
// sine.h - A sine function
//
// `sine(frequency)` returns a sine wave with the given frequency.
//
#ifndef CSYNTH_SINE_H
#define CSYNTH_SINE_H

#include <math.h>

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double output;
    double direction;
} SineContext;

static double sine_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    SineContext *context = (SineContext *)context_;
    double frequency = gen_eval(args[0]);
    double factor = 2.0 * M_PI * frequency * delta;
    double next = asin(context->output) * context->direction + factor;
    double output = context->output;
    context->output = sin(context->direction * next);
    context->direction = (int)round(next / M_PI) % 2 == 0 ? context->direction : -context->direction;
    return output;
}

Func *sine(Func *frequency)
{
    SineContext initial = (SineContext){
        .direction = 1.0,
    };
    return func_create(NULL, sine_eval, NULL, sizeof(SineContext), &initial, 1, frequency);
}

Func *sine_(double frequency) { return sine(const_(frequency)); }

void test_sine()
{
    Func *t = sine(const_(1));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0000000000000000);
    assert_gen_equal(g, 0.5877852522924731);
    assert_gen_equal(g, 0.9510565162951535);
    assert_gen_equal(g, 0.9510565162951536);
    assert_gen_equal(g, 0.5877852522924732);
    assert_gen_equal(g, 0.0000000000000002);
    assert_gen_equal(g, -0.5877852522924729);
    assert_gen_equal(g, -0.9510565162951535);
    assert_gen_equal(g, -0.9510565162951536);
    assert_gen_equal(g, -0.5877852522924732);
    assert_gen_equal(g, -0.0000000000000002);
    assert_gen_equal(g, 0.5877852522924729);
}

#endif // CSYNTH_SINE_H
