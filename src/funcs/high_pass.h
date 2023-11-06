//
// high_pass.h - A first-order high-pass filter
//
// `high_pass(input, frequency)` with input and frequency functions.
//
#ifndef COMPOSER_HIGH_PASS_H
#define COMPOSER_HIGH_PASS_H

#include <assert.h>
#include <math.h>

#include "../core/func.h"
#include "./cons.h"

typedef struct
{
    double input;
    double output;
} HighPassContext;

double high_pass_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    HighPassContext *context = (HighPassContext *)_context;
    double input = gen_eval(args[0]);
    double frequency = gen_eval(args[1]);
    double factor = (frequency * 2.0 * M_PI * delta) + 1.0;
    double output = context->output;
    context->output = (context->output + input - context->input) / factor;
    context->input = input;
    return output;
}

Func *high_pass(Func *input, Func *frequency)
{
    return func_create(NULL, high_pass_eval, NULL, sizeof(HighPassContext), NULL, 2, input, frequency);
}

void test_high_pass()
{
    func t = high_pass(cons(1), cons(10));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-4;
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.137303) < epsilon);
    assert(fabs(gen_eval(g) - 0.018852) < epsilon);
    assert(fabs(gen_eval(g) - 0.002588) < epsilon);
    assert(fabs(gen_eval(g) - 0.000355) < epsilon);
    assert(fabs(gen_eval(g) - 0.000049) < epsilon);
    assert(fabs(gen_eval(g) - 0.000007) < epsilon);
    assert(fabs(gen_eval(g) - 0.000001) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
}

#endif // COMPOSER_HIGH_PASS_H
