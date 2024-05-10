//
// knob.h - Trigger based on key knob
//
#ifndef CSYNTH_KNOB_H
#define CSYNTH_KNOB_H

#include <float.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

#include "../../util/key_event.h"

typedef struct
{
    KeyEventContext parent;
    int key;
    double value;
    double step;
    double min;
    double max;
    int rel;
    int active;
} KnobContext;

static double knob_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    return context->value;
}

int knob_listener(int key, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    if (key == context->key)
    {
        context->active = 1;
    }
    else if (context->active && key == KEY_EVENT_UP)
    {
        if (context->rel)
        {
            context->value *= (1 + context->step);
        }
        else
        {
            context->value += context->step;
        }
        if (context->value > context->max)
        {
            context->value = context->max;
        }
    }
    else if (context->active && key == KEY_EVENT_DOWN)
    {
        if (context->rel)
        {
            context->value /= (1 + context->step);
        }
        else
        {
            context->value -= context->step;
        }
        if (context->value < context->min)
        {
            context->value = context->min;
        }
    }
    else
    {
        context->active = 0;
    }
    return 0;
}

Func *knob_range(int key, double value, double step, double min, double max, int rel)
{
    KnobContext initial = (KnobContext){
        .parent = {.key_listener = knob_listener},
        .key = key,
        .value = value,
        .step = step,
        .min = min,
        .max = max,
        .rel = rel,
    };
    return func_create(key_event_init, knob_eval, key_event_free, sizeof(KnobContext), &initial, FUNC_FLAG_NO_RESET, 0);
}

Func *knob(int key, double value, double delta)
{
    return knob_range(key, value, delta, -FLT_MAX, FLT_MAX, 0);
}

Func *knob_rel(int key, double value, double perc)
{
    return knob_range(key, value, perc, -FLT_MAX, FLT_MAX, 1);
}

#endif // CSYNTH_KNOB_H
