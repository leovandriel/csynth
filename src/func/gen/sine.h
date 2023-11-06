//
// sine.h - A sine function
//
// `sine(frequency)` returns a sine wave with the given frequency.
//
#ifndef CSYNTH_SINE_H
#define CSYNTH_SINE_H

#include <assert.h>
#include <math.h>

#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double output;
    double direction;
} SineContext;

double sine_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    SineContext *context = (SineContext *)_context;
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

#define sine_(_frequency) (sine(const_(_frequency)))

void test_sine()
{
    func t = sine(const_(1));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-5;
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.587785) < epsilon);
    assert(fabs(gen_eval(g) - 0.951057) < epsilon);
    assert(fabs(gen_eval(g) - 0.951057) < epsilon);
    assert(fabs(gen_eval(g) - 0.587785) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - -0.587785) < epsilon);
    assert(fabs(gen_eval(g) - -0.951057) < epsilon);
    assert(fabs(gen_eval(g) - -0.951057) < epsilon);
    assert(fabs(gen_eval(g) - -0.587785) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.587785) < epsilon);
    assert(fabs(gen_eval(g) - 0.951057) < epsilon);
}

#endif // CSYNTH_SINE_H
