//
// trigger.h - Trigger based on key trigger
//
#ifndef CSYNTH_TRIGGER_H
#define CSYNTH_TRIGGER_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"

typedef struct
{
    ControlEventContext parent;
    ControlEventKey key;
    int on;
    int reset;
} TriggerContext;

static double trigger_eval(__U int count, __U Gen **args, EvalContext *eval, void *context_)
{
    TriggerContext *context = (TriggerContext *)context_;
    if (context->reset != 0)
    {
        gen_reset(args[0]);
        context->reset = 0;
    }
    return context->on ? gen_eval(args[0], eval) : 0;
}

static void trigger_handle_event(ControlEvent *event, void *context_)
{
    TriggerContext *context = (TriggerContext *)context_;
    if (control_event_key_equal(event->key, context->key))
    {
        context->on = 1;
        context->reset = 1;
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeTrigger, &context->on);
    }
}

static int trigger_init(__U int count, __U Gen **args, void *context_)
{
    TriggerContext *context = (TriggerContext *)context_;
    state_event_broadcast(0, StateEventKeyTypeControl, &context->key, StateEventValueTypeTrigger, &context->on);
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

Func *trigger_create(int key, Func *input)
{
    TriggerContext initial = {
        .parent = {.handle_event = trigger_handle_event},
        .key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        }};
    return func_create(trigger_init, trigger_eval, control_event_free, sizeof(TriggerContext), &initial, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_TRIGGER_H
