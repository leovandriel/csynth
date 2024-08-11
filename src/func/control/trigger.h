#ifndef CSYNTH_TRIGGER_H
#define CSYNTH_TRIGGER_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"

/** @see trigger_create */
typedef struct
{
    /** @brief Super struct, allowing use of control_event_free. */
    ControlEventContext parent;
    /** @brief Key to trigger the input. */
    ControlEventKey key;
    /** @brief Flag to indicate it was triggered. */
    bool on;
    /** @brief Flag to indicate it generator needs to be reset. */
    bool reset;
} TriggerContext;

static double trigger_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    TriggerContext *context = (TriggerContext *)context_;
    if (context->reset)
    {
        gen_reset(args[0]);
        context->reset = false;
    }
    return context->on ? gen_eval(args[0], eval) : 0;
}

static void trigger_handle_event(ControlEvent *event, void *context_)
{
    TriggerContext *context = (TriggerContext *)context_;
    if (control_event_key_equal(event->key, context->key))
    {
        context->on = true;
        context->reset = true;
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeTrigger, &context->on);
    }
}

static int trigger_init(__U size_t count, __U Gen **args, void *context_)
{
    TriggerContext *context = (TriggerContext *)context_;
    state_event_broadcast(0, StateEventKeyTypeControl, &context->key, StateEventValueTypeTrigger, &context->on);
    return control_event_add(&context->parent);
}

/**
 * @brief Create function to trigger an input function with a key stroke.
 *
 * This function will output 0 until the key is pressed, then it will sample the
 * input function.
 *
 * @param key Key index to listen for.
 * @param input Input function to trigger.
 * @return Func* Trigger function.
 */
Func *trigger_create(int key, Func *input)
{
    TriggerContext initial = {
        .parent = {.handle_event = trigger_handle_event},
        .key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        }};
    return func_create(trigger_init, trigger_eval, control_event_free, NULL, sizeof(TriggerContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_TRIGGER_H
