//
// selector.h - Trigger based on key select
//
#ifndef CSYNTH_SELECTOR_H
#define CSYNTH_SELECTOR_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"

typedef struct
{
    ControlEventContext parent;
    ControlEventKey key;
    int count;
    int selected;
} SelectorContext;

static double selector_eval(__U int count, __U Gen **args, EvalContext *eval, void *context_)
{
    SelectorContext *context = (SelectorContext *)context_;
    return gen_eval(args[context->selected], eval);
}

static void selector_handle_event(ControlEvent *event, void *context_)
{
    SelectorContext *context = (SelectorContext *)context_;
    if (control_event_key_equal(event->key, context->key))
    {
        context->selected = (context->selected + 1) % context->count;
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeInt, &context->selected);
    }
}

static int selector_init(__U int count, __U Gen **args, void *context_)
{
    SelectorContext *context = (SelectorContext *)context_;
    state_event_broadcast(0, StateEventKeyTypeControl, &context->key, StateEventValueTypeInt, &context->selected);
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

Func *selector_create(int key, int count, Func **args)
{
    SelectorContext initial = {
        .parent = {.handle_event = selector_handle_event},
        .key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        },
        .count = count,
    };
    return func_create(selector_init, selector_eval, control_event_free, sizeof(SelectorContext), &initial, FuncFlagSkipReset, count, args);
}

#endif // CSYNTH_SELECTOR_H
