//
// step.h - A step function
//
// `step(at)` returns 1 if time is past at, otherwise 0.
// - block(edge0, edge1) - A block function, which is 1 between edge0 and edge1
// - block_ - Take double arguments instead of functions
//
#ifndef COMPOSER_STEP_H
#define COMPOSER_STEP_H

#include <assert.h>
#include <math.h>

#include "../core/func.h"
#include "./cons.h"

typedef struct
{
    double time;
} StepContext;

double step_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
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

#define block(_edge0, _edge1) mul(step(_edge0), add(ONE, neg(step(_edge1))))
#define block_(_edge0, _edge1) block(cons(_edge0), cons(_edge1))

void test_step()
{
    func t = step(cons(0.5));
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

#endif // COMPOSER_STEP_H
