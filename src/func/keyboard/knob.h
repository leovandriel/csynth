//
// knob.h - Trigger based on key knob
//
#ifndef CSYNTH_KNOB_H
#define CSYNTH_KNOB_H

#include <float.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

#include "../../event/keyboard_event.h"
#include "../../event/state_event.h"

typedef struct
{
    KeyboardEventContext parent;
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

static void knob_listener(int key, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    if (key == context->key && !context->active)
    {
        context->active = 1;
        state_event_broadcast(context->key, StateEventTypeSelected, &context->active);
    }
    else if (context->active && key == KEYBOARD_EVENT_UP)
    {
        if (context->rel != 0)
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
        state_event_broadcast(context->key, StateEventTypeDouble, &context->value);
    }
    else if (context->active && key == KEYBOARD_EVENT_DOWN)
    {
        if (context->rel != 0)
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
        state_event_broadcast(context->key, StateEventTypeDouble, &context->value);
    }
    else
    {
        context->active = 0;
        state_event_broadcast(context->key, StateEventTypeSelected, &context->active);
    }
}

static int knob_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    state_event_broadcast(context->key, StateEventTypeDouble, &context->value);
    csError error = keyboard_event_add(&context->parent);
    return error_catch(error);
}

Func *knob_range(int key, double value, double step, double min, double max, int rel)
{
    KnobContext initial = (KnobContext){
        .parent = {.keyboard_listener = knob_listener},
        .key = key,
        .value = value,
        .step = step,
        .min = min,
        .max = max,
        .rel = rel,
    };
    return func_create(knob_init, knob_eval, keyboard_event_free, sizeof(KnobContext), &initial, FUNC_FLAG_SKIP_RESET, 0);
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
