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
    StateEventKeyTypeControl = 1,
    StateEventKeyTypeLabel = 4,
} StateEventKeyType;

typedef enum
{
    StateEventValueTypeNone = 0,
    StateEventValueTypeBool = 1,
    StateEventValueTypeBoolInv = 2,
    StateEventValueTypeTrigger = 3,
    StateEventValueTypeInt = 4,
    StateEventValueTypeSize = 5,
    StateEventValueTypeDouble = 6,
    StateEventValueTypeScientific = 7,
    StateEventValueTypeSelected = 8,
} StateEventValueType;

typedef struct
{
    double time;
    StateEventKeyType key_type;
    const void *key;
    StateEventValueType value_type;
    const void *value;
} StateEvent;

typedef void (*state_handle_event)(StateEvent *event, void *context);

typedef struct
{
    const void *handler;
    state_handle_event handle_event;
} StateEventContext;

void state_event_broadcast(double time, StateEventKeyType key_type, const void *key, StateEventValueType value_type, const void *value)
{
    StateEvent event = {
        .time = time,
        .key_type = key_type,
        .key = key,
        .value_type = value_type,
        .value = value,
    };
    event_broadcast(EventTypeState, &event);
}

void state_event_handle_event(EventType type, const void *event_, void *context_)
{
    StateEventContext *context = (StateEventContext *)context_;
    if (type == EventTypeState)
    {
        StateEvent *event = (StateEvent *)event_;
        context->handle_event(event, context);
    }
}

csError state_event_add(StateEventContext *context)
{
    const void *handler = event_add_handler(state_event_handle_event, context);
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
