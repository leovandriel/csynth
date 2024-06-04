//
// step.h - A step function
//
// `step(at)` returns 1 if time is past at, otherwise 0.
// - block(edge0, edge1) - A block function, which is 1 between edge0 and edge1
// - block_ - Take double arguments instead of functions
//
#ifndef CSYNTH_STEP_H
#define CSYNTH_STEP_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"
#include "../op/mul.h"

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

Func *step_env(Func *edge)
{
    return func_create(NULL, step_eval, NULL, sizeof(StepContext), NULL, FUNC_FLAG_DEFAULT, 1, edge);
}

Func *step_env_(double edge) { return step_env(const_(edge)); }
Func *step(Func *f, Func *edge) { return mul(f, step_env(edge)); }
Func *step_(Func *f, double edge) { return step(f, const_(edge)); }

#endif // CSYNTH_STEP_H
