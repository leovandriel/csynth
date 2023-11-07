//
// step.h - A step function
//
// `step(at)` returns 1 if time is past at, otherwise 0.
// - block(edge0, edge1) - A block function, which is 1 between edge0 and edge1
// - block_ - Take double arguments instead of functions
//
#ifndef CSYNTH_STEP_H
#define CSYNTH_STEP_H

#include <assert.h>
#include <math.h>

#include "../../core/func.h"
#include "../gen/const.h"
#include "../op/mul.h"
#include "../op/neg.h"
#include "../env/step.h"

typedef struct
{
    double time;
} StepContext;

static double step_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    StepContext *context = (StepContext *)_context;
    double edge = gen_eval(args[0]);
    double value = context->time < edge ? 0.0 : 1.0;
    context->time += delta;
    return value;
}

Func *step(Func *edge)
{
    return func_create(NULL, step_eval, NULL, sizeof(StepContext), NULL, 1, edge);
}

Func *step_inv(Func *edge) { return sub(ONE, step(edge)); }
Func *step_(double edge) { return step(const_(edge)); }
Func *step_inv_(double edge) { return step_inv(const_(edge)); }
Func *block(Func *edge0, Func *edge1) { return mul(step(edge0), step_inv(edge1)); }
Func *block_(double edge0, double edge1) { return block(const_(edge0), const_(edge1)); }

void test_step()
{
    Func *t = step(const_(0.5));
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
    assert(fabs(gen_eval(g) - 1.0) < epsilon);
}

#endif // CSYNTH_STEP_H
