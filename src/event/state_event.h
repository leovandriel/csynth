//
// state_event.h - Func lifecyle for state events
//
#ifndef CSYNTH_STATE_EVENT_H
#define CSYNTH_STATE_EVENT_H

#include "../core/gen.h"
#include "./event.h"

typedef enum
{
    StateEventTypeNone = 0,
    StateEventTypeBool = 1,
    StateEventTypeBoolInv = 2,
    StateEventTypeTrigger = 3,
    StateEventTypeInt = 4,
    StateEventTypeDouble = 5,
    StateEventTypeSelected = 6,
} StateEventType;

typedef void (*state_event_listener)(int key, StateEventType type, void *value, void *context);

typedef struct
{
    int key;
    StateEventType type;
    void *value;
} StateEvent;

typedef struct
{
    void *handle;
    state_event_listener state_listener;
} StateEventContext;

void state_event_broadcast(int key, StateEventType type, void *value)
{
    StateEvent event = {.key = key, .type = type, .value = value};
    event_broadcast(EventTypeState, &event);
}

void state_event_listen(EventType type, void *event_, void *context_)
{
    StateEventContext *context = (StateEventContext *)context_;
    if (type == EventTypeState)
    {
        StateEvent *event = (StateEvent *)event_;
        context->state_listener(event->key, event->type, event->value, context);
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
