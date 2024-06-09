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

typedef int (*state_event_listener)(int key, StateEventType type, void *value, void *context);

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

int state_event_broadcast(int key, StateEventType type, void *value)
{
    StateEvent event = {.key = key, .type = type, .value = value};
    return event_broadcast(EventTypeState, &event);
}

int state_event_listen(EventType type, void *event_, void *context_)
{
    StateEventContext *context = (StateEventContext *)context_;
    if (type == EventTypeState)
    {
        StateEvent *event = (StateEvent *)event_;
        return context->state_listener(event->key, event->type, event->value, context);
    }
    return 0;
}

void state_event_add(StateEventContext *context)
{
    context->handle = event_add_listener(state_event_listen, context);
}

void state_event_remove(StateEventContext *context)
{
    event_remove_listener(context->handle);
    context->handle = NULL;
}

#endif // CSYNTH_STATE_EVENT_H
