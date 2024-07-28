#ifndef CSYNTH_STEPPER_H
#define CSYNTH_STEPPER_H

#include <float.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"
#include "../gen/const.h"

/** @see stepper_create */
typedef struct
{
    /** @brief Super struct, allowing use of control_event_free. */
    ControlEventContext parent;
    /** @brief Key to trigger the input. */
    ControlEventKey key;
    /** @brief Current value. */
    double value;
    /** @brief Step size. */
    double step;
    /** @brief Minimum value. */
    double min;
    /** @brief Maximum value. */
    double max;
    /** @brief Flag to increase relative or absolute. */
    bool rel;
    /** @brief Flag to indicate it is in listening state. */
    bool active;
} StepperContext;

static double stepper_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    StepperContext *context = (StepperContext *)context_;
    return context->value;
}

static void stepper_handle_event(ControlEvent *event, void *context_)
{
    StepperContext *context = (StepperContext *)context_;
    if (control_event_key_equal(event->key, context->key) && !context->active)
    {
        context->active = true;
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeSelected, &context->active);
    }
    else if (context->active && event->key.keyboard == KEYBOARD_EVENT_UP)
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
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeDouble, &context->value);
    }
    else if (context->active && event->key.keyboard == KEYBOARD_EVENT_DOWN)
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
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeDouble, &context->value);
    }
    else
    {
        context->active = false;
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeSelected, &context->active);
    }
}

static int stepper_init(__U size_t count, __U Gen **args, void *context_)
{
    StepperContext *context = (StepperContext *)context_;
    state_event_broadcast(0, StateEventKeyTypeControl, &context->key, StateEventValueTypeDouble, &context->value);
    return control_event_add(&context->parent);
}

/**
 * @brief Create function to step up/down through values based on key stroke.
 *
 * @param key Key index to listen for.
 * @param value Initial output value.
 * @param step Step size.
 * @param min Minimum output value.
 * @param max Maximum output value.
 * @param rel Flag to increase relative or absolute.
 * @return Func* Stepper function.
 */
Func *stepper_create(int key, double value, double step, double min, double max, bool rel)
{
    StepperContext initial = {
        .parent = {.handle_event = stepper_handle_event},
        .key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        },
        .value = value,
        .step = step,
        .min = min,
        .max = max,
        .rel = rel,
    };
    return func_create(stepper_init, stepper_eval, control_event_free, sizeof(StepperContext), &initial, FuncFlagSkipReset, );
}

#endif // CSYNTH_STEPPER_H
