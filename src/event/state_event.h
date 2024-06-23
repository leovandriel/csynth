//
// state_event.h - Func lifecyle for state events
//
#ifndef CSYNTH_STATE_EVENT_H
#define CSYNTH_STATE_EVENT_H

#include "../core/gen.h"
#include "./event.h"

typedef enum
{
    StateEventKeyTypeNone = 0,
    StateEventKeyTypeKeyboard = 1,
    StateEventKeyTypeMidi = 2,
    StateEventKeyTypeLabel = 3,
} StateEventKeyType;

typedef enum
{
    StateEventValueTypeNone = 0,
    StateEventValueTypeBool = 1,
    StateEventValueTypeBoolInv = 2,
    StateEventValueTypeTrigger = 3,
    StateEventValueTypeInt = 4,
    StateEventValueTypeDouble = 5,
    StateEventValueTypeSelected = 6,
} StateEventValueType;

typedef void (*state_handle_event)(StateEventKeyType key_type, const void *key, StateEventValueType value_type, const void *value, void *context);

typedef struct
{
    StateEventKeyType key_type;
    const void *key;
    StateEventValueType value_type;
    const void *value;
} StateEvent;

typedef struct
{
    const void *handler;
    state_handle_event handle_event;
} StateEventContext;

void state_event_broadcast(StateEventKeyType key_type, const void *key, StateEventValueType value_type, const void *value)
{
    StateEvent event = {.key_type = key_type, .key = key, .value_type = value_type, .value = value};
    event_broadcast(EventTypeState, &event);
}

void state_handle_event_(EventType type, const void *event_, void *context_)
{
    StateEventContext *context = (StateEventContext *)context_;
    if (type == EventTypeState)
    {
        StateEvent *event = (StateEvent *)event_;
        context->handle_event(event->key_type, event->key, event->value_type, event->value, context);
    }
}

csError state_event_add(StateEventContext *context)
{
    const void *handler = event_add_handler(state_handle_event_, context);
    if (handler == NULL)
    {
        return error_type_message(csErrorInit, "Unable to add state event handler");
    }
    context->handler = handler;
    return csErrorNone;
}

csError state_event_remove(StateEventContext *context)
{
    csError error = event_remove_handler(context->handler);
    if (error != csErrorNone)
    {
        return error;
    }
    context->handler = NULL;
    return csErrorNone;
}

#endif // CSYNTH_STATE_EVENT_H
