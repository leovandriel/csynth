//
// state_event.h - Func lifecyle for state events
//
#ifndef CSYNTH_STATE_EVENT_H
#define CSYNTH_STATE_EVENT_H

#include "../core/gen.h"
#include "./event.h"

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

typedef enum
{
    StateEventKeyTypeNone = 0,
    StateEventKeyTypeKeyboard = 1,
    StateEventKeyTypeMidi = 2,
} StateEventKeyType;

typedef void (*state_event_listener)(StateEventKeyType key_type, void *key, StateEventValueType value_type, void *value, void *context);

typedef struct
{
    StateEventKeyType key_type;
    void *key;
    StateEventValueType value_type;
    void *value;
} StateEvent;

typedef struct
{
    void *handle;
    state_event_listener state_listener;
} StateEventContext;

void state_event_broadcast(StateEventKeyType key_type, void *key, StateEventValueType value_type, void *value)
{
    StateEvent event = {.key_type = key_type, .key = key, .value_type = value_type, .value = value};
    event_broadcast(EventTypeState, &event);
}

void state_event_listen(EventType type, void *event_, void *context_)
{
    StateEventContext *context = (StateEventContext *)context_;
    if (type == EventTypeState)
    {
        StateEvent *event = (StateEvent *)event_;
        context->state_listener(event->key_type, event->key, event->value_type, event->value, context);
    }
}

csError state_event_add(StateEventContext *context)
{
    void *handle = event_add_listener(state_event_listen, context);
    if (handle == NULL)
    {
        return error_type_message(csErrorInit, "Unable to add state event listener");
    }
    context->handle = handle;
    return csErrorNone;
}

csError state_event_remove(StateEventContext *context)
{
    csError error = event_remove_listener(context->handle);
    if (error != csErrorNone)
    {
        return error;
    }
    context->handle = NULL;
    return csErrorNone;
}

#endif // CSYNTH_STATE_EVENT_H
