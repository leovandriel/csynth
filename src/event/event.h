//
// event.h - Manage event listeners
//
#ifndef CSYNTH_EVENT_H
#define CSYNTH_EVENT_H

#include <stdio.h>
#include <string.h>

#include "../mem/alloc.h"
#include "../util/error.h"

typedef enum
{
    EventTypeNone = 0,
    EventTypeKeyboard = 1,
    EventTypeState = 2,
    EventTypeMidi = 3,
} EventType;

typedef void (*event_listener)(EventType type, void *event, void *context);

typedef struct EventListener
{
    event_listener listener;
    void *context;
    struct EventListener *next;
} EventListener;

EventListener *event_listener_list = NULL;

void *event_add_listener(event_listener listener, void *context)
{
    EventListener *handle = (EventListener *)malloc_(sizeof(EventListener));
    if (handle == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    *handle = (EventListener){.listener = listener, .context = context, .next = event_listener_list};
    event_listener_list = handle;
    return handle;
}

csError event_remove_listener(void *handle)
{
    EventListener **prev = &event_listener_list;
    for (EventListener *listener = event_listener_list; listener; listener = listener->next)
    {
        if (listener == handle)
        {
            *prev = listener->next;
            free_(listener);
            return csErrorNone;
        }
        prev = &listener->next;
    }
    return error_type_message(csErrorNotFound, "Event listener not found");
}

void event_clear()
{
    while (event_listener_list)
    {
        EventListener *next = event_listener_list->next;
        free_(event_listener_list);
        event_listener_list = next;
    }
}

void event_broadcast(EventType type, void *event)
{
    for (EventListener *handler = event_listener_list; handler; handler = handler->next)
    {
        handler->listener(type, event, handler->context);
    }
}

#endif // CSYNTH_EVENT_H
