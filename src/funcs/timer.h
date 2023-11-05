//
// timer.h - The sample time
//
// `timer()` returns accumulated time deltas
//
#ifndef COMPOSER_TIMER_H
#define COMPOSER_TIMER_H

#include "../core/func.h"

typedef struct
{
    double output;
} TimerContext;

double timer_eval(__attribute__((unused)) Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    TimerContext *context = (TimerContext *)_context;
    context->output += delta;
    return context->output;
}

Func *timer()
{
    return func_create(NULL, timer_eval, NULL, sizeof(TimerContext), NULL, 0);
}

#endif // COMPOSER_TIMER_H
