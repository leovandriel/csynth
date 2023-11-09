//
// saw.h - A sawtooth function
//
// `saw(frequency)` returns a sawtooth wave with the given frequency.
//
#ifndef CSYNTH_SAW_H
#define CSYNTH_SAW_H

#include <math.h>

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double output;
} SawContext;

static double saw_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    SawContext *context = (SawContext *)context_;
    double frequency = gen_eval(args[0]);
    double output = context->output;
    context->output += 2.0 * frequency * delta;
    if (context->output > 1.0)
    {
        context->output -= 2.0;
    }
    return output;
}

Func *saw(Func *frequency)
{
    return func_create(NULL, saw_eval, NULL, sizeof(SawContext), NULL, 1, frequency);
}

Func *saw_(double frequency) { return saw(const_(frequency)); }

void test_saw()
{
    Func *t = saw(const_(1));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.2);
    assert_gen_equal(g, 0.4);
    assert_gen_equal(g, 0.6);
    assert_gen_equal(g, 0.8);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, -0.8);
    assert_gen_equal(g, -0.6);
    assert_gen_equal(g, -0.4);
    assert_gen_equal(g, -0.2);
    assert_gen_equal(g, -0.0);
}

#endif // CSYNTH_SAW_H
