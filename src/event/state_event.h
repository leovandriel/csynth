#ifndef CSYNTH_STATE_EVENT_H
#define CSYNTH_STATE_EVENT_H

#include "../core/gen.h"
#include "./event.h"

typedef enum
{
    StateEventKeyTypeNone = 0,
    StateEventKeyTypeControl,
    StateEventKeyTypeLabel,
} StateEventKeyType;

typedef enum
{
    StateEventValueTypeNone = 0,
    StateEventValueTypeBool,
    StateEventValueTypeBoolInv,
    StateEventValueTypeTrigger,
    StateEventValueTypeInt,
    StateEventValueTypeSize,
    StateEventValueTypeDouble,
    StateEventValueTypeScientific,
    StateEventValueTypeSelected,
} StateEventValueType;

/**
 * @brief State change event, at a specific time.
 */
typedef struct
{
    /** @brief Time in seconds. */
    double time;
    /** @brief Type of event key. */
    StateEventKeyType key_type;
    /** @brief Event key data. */
    const void *key;
    /** @brief Type of event value. */
    StateEventValueType value_type;
    /** @brief Event value data. */
    const void *value;
} StateEvent;

typedef void (*state_handle_event)(StateEvent *event, void *context);

/** @see state_event_create */
typedef struct
{
    /** @brief Handle to the event listener. */
    const void *handler;
    /** @brief Handle event callback. */
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
