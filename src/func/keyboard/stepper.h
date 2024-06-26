//
// stepper.h - Control in steps
//
#ifndef CSYNTH_STEPPER_H
#define CSYNTH_STEPPER_H

#include <float.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/keyboard_event.h"
#include "../../event/state_event.h"
#include "../gen/const.h"

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
} StepperContext;

static double stepper_eval(__U int count, __U Gen **args, __U Eval eval, void *context_)
{
    StepperContext *context = (StepperContext *)context_;
    return context->value;
}

static void stepper_handle_event(int key, void *context_)
{
    StepperContext *context = (StepperContext *)context_;
    if (key == context->key && !context->active)
    {
        context->active = 1;
        state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeSelected, &context->active);
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
        state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeDouble, &context->value);
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
        state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeDouble, &context->value);
    }
    else
    {
        context->active = 0;
        state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeSelected, &context->active);
    }
}

static int stepper_init(__U int count, __U Gen **args, void *context_)
{
    StepperContext *context = (StepperContext *)context_;
    state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeDouble, &context->value);
    csError error = keyboard_event_add(&context->parent);
    return error_catch(error);
}

Func *stepper_create(int key, double value, double step, double min, double max, int rel)
{
    StepperContext initial = {
        .parent = {.handle_event = stepper_handle_event},
        .key = key,
        .value = value,
        .step = step,
        .min = min,
        .max = max,
        .rel = rel,
    };
    return func_create(stepper_init, stepper_eval, keyboard_event_free, sizeof(StepperContext), &initial, FuncFlagSkipReset, FUNCS());
}

#endif // CSYNTH_STEPPER_H
