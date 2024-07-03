//
// timer.h - The sample time
//
#ifndef CSYNTH_TIMER_H
#define CSYNTH_TIMER_H

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double time;
} TimerContext;

static double timer_eval(__U int count, Gen **args, Eval *eval, void *context_)
{
    TimerContext *context = (TimerContext *)context_;
    double output = context->time;
    double tick = gen_eval(args[0], eval);
    context->time += tick;
    return output;
}

Func *timer_create(Func *tick)
{
    return func_create(NULL, timer_eval, NULL, sizeof(TimerContext), NULL, FuncFlagNone, FUNCS(tick));
}

#endif // CSYNTH_TIMER_H
