//
// timer.h - The sample time
//
// `timer()` returns accumulated time deltas
//
#ifndef CSYNTH_TIMER_H
#define CSYNTH_TIMER_H

#include <assert.h>
#include <math.h>

#include "../../core/func.h"

typedef struct
{
    double time;
} TimerContext;

static double timer_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, double delta, void *context_)
{
    TimerContext *context = (TimerContext *)context_;
    double output = context->time;
    context->time += delta;
    return output;
}

Func *timer()
{
    return func_create(NULL, timer_eval, NULL, sizeof(TimerContext), NULL, 0);
}

void test_timer()
{
    Func *t = timer();
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.1) < epsilon);
    assert(fabs(gen_eval(g) - 0.2) < epsilon);
    assert(fabs(gen_eval(g) - 0.3) < epsilon);
    assert(fabs(gen_eval(g) - 0.4) < epsilon);
}

#endif // CSYNTH_TIMER_H
