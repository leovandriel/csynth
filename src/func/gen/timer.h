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
    double output;
} TimerContext;

double timer_eval(__attribute__((unused)) Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    TimerContext *context = (TimerContext *)_context;
    double output = context->output;
    context->output += delta;
    return output;
}

Func *timer()
{
    return func_create(NULL, timer_eval, NULL, sizeof(TimerContext), NULL, 0);
}

void test_timer()
{
    func t = timer();
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 0.0) < epsilon);
    assert(fabs(gen_eval(g) - 0.1) < epsilon);
    assert(fabs(gen_eval(g) - 0.2) < epsilon);
    assert(fabs(gen_eval(g) - 0.3) < epsilon);
    assert(fabs(gen_eval(g) - 0.4) < epsilon);
}

#endif // CSYNTH_TIMER_H
