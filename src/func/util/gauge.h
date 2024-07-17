//
// gauge.h - Broadcasts the output value for display
//
#ifndef CSYNTH_GAUGE_H
#define CSYNTH_GAUGE_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/state_event.h"

typedef struct
{
    const char *label;
    double last;
    double time;
} GaugeContext;

static double gauge_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    GaugeContext *context = (GaugeContext *)context_;
    double input = gen_eval(args[1], eval);
    if (context->time >= 1.0 && input != context->last)
    {
        state_event_broadcast(eval->wall_time, StateEventKeyTypeLabel, context->label, StateEventValueTypeDouble, &input);
        context->last = input;
        context->time = 0.0;
    }
    double tick = gen_eval(args[0], eval);
    context->time += tick;
    return input;
}

Func *gauge_create(const char *label, Func *tick, Func *input)
{
    GaugeContext initial = {
        .label = label,
        .time = 1.0,
    };
    return func_create(NULL, gauge_eval, NULL, sizeof(GaugeContext), &initial, FuncFlagNone, tick, input);
}

#endif // CSYNTH_GAUGE_H
