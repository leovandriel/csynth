//
// step.h - A step function
//
// `step(at)` returns 1 if time is past at, otherwise 0.
// - block(edge0, edge1) - A block function, which is 1 between edge0 and edge1
// - block_ - Take double arguments instead of functions
//
#ifndef CSYNTH_STEP_H
#define CSYNTH_STEP_H

#include "../../util/test.h"
#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double time;
} StepContext;

static double step_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    StepContext *context = (StepContext *)context_;
    double edge = gen_eval(args[0]);
    double value = context->time < edge ? 0.0 : 1.0;
    context->time += delta;
    return value;
}

Func *step(Func *edge)
{
    return func_create(NULL, step_eval, NULL, sizeof(StepContext), NULL, 1, edge);
}

Func *step_(double edge) { return step(const_(edge)); }

void test_step()
{
    Func *t = step(const_(0.5));
    Gen *g = gen_create(t, 0.1);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 0.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
    assert_gen_equal(g, 1.0);
}

#endif // CSYNTH_STEP_H
