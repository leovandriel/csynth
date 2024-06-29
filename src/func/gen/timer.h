//
// timer.h - The sample time
//
// `timer()` returns accumulated time deltas
//
#ifndef CSYNTH_TIMER_H
#define CSYNTH_TIMER_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double time;
} TimerContext;

static double timer_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    TimerContext *context = (TimerContext *)context_;
    double output = context->time;
    context->time += eval.tick[EvalTickPitch];
    return output;
}

Func *timer()
{
    return func_create(NULL, timer_eval, NULL, sizeof(TimerContext), NULL, FuncFlagNone, FUNCS());
}

#endif // CSYNTH_TIMER_H
