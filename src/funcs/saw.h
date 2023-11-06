//
// saw.h - A sawtooth function
//
// `saw(frequency)` returns a sawtooth wave with the given frequency.
//
#ifndef CSYNTH_SAW_H
#define CSYNTH_SAW_H

#include <assert.h>
#include <math.h>

#include "../core/func.h"
#include "./const.h"

typedef struct
{
    double output;
} SawContext;

double saw_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    SawContext *context = (SawContext *)_context;
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

#define saw_(_frequency) (saw(const_(_frequency)))

void test_saw()
{
    func t = saw(const_(1));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.2) < epsilon);
    assert(fabs(gen_eval(g) - 0.4) < epsilon);
    assert(fabs(gen_eval(g) - 0.6) < epsilon);
    assert(fabs(gen_eval(g) - 0.8) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - -0.8) < epsilon);
    assert(fabs(gen_eval(g) - -0.6) < epsilon);
    assert(fabs(gen_eval(g) - -0.4) < epsilon);
    assert(fabs(gen_eval(g) - -0.2) < epsilon);
    assert(fabs(gen_eval(g) - -0.0) < epsilon);
}

#endif // CSYNTH_SAW_H
