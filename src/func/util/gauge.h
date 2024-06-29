//
// gauge.h - Broadcasts the output value for display
//
#ifndef CSYNTH_GAUGE_H
#define CSYNTH_GAUGE_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/state_event.h"
#include "../../ui/display.h"

#define GAUGE_DEFAULT_DISPLAY_INTERVAL 0.01 // 100 FPS

typedef struct
{
    const char *label;
    double last;
    double time;
    double interval;
} GaugeContext;

static double gauge_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    GaugeContext *context = (GaugeContext *)context_;
    double input = gen_eval(args[0], eval);
    if (context->time >= context->interval && input != context->last)
    {
        state_event_broadcast(StateEventKeyTypeLabel, context->label, StateEventValueTypeDouble, &input);
        context->last = input;
        context->time = 0;
    }
    context->time += eval.step[EvalStepAudio];
    return input;
}

Func *gauge_interval(Func *input, const char *label, double interval)
{
    GaugeContext initial = {
        .label = label,
        .interval = interval,
        .time = interval,
    };
    display_label(label);
    return func_create(NULL, gauge_eval, NULL, sizeof(GaugeContext), &initial, FuncFlagNone, FUNCS(input));
}

Func *gauge(Func *input, const char *label)
{
    return gauge_interval(input, label, GAUGE_DEFAULT_DISPLAY_INTERVAL);
}

Func *display(Func *input, const char *label)
{
    return gauge(input, label);
}

#endif // CSYNTH_GAUGE_H
