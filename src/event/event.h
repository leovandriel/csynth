//
// event.h - Manage event listeners
//
#ifndef CSYNTH_EVENT_H
#define CSYNTH_EVENT_H

#include <stdio.h>
#include <string.h>

#include "../mem/alloc.h"

typedef enum
{
    EventTypeNone = 0,
    EventTypeKeyboard = 1,
    EventTypeState = 2,
    EventTypeMidi = 3,
} EventType;

typedef int (*event_listener)(EventType type, void *event, void *context);

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
    if (!handle)
    {
        fprintf(stderr, "event_add_listener: unable to allocate memory\n");
        return NULL;
    }
    handle->listener = listener;
    handle->context = context;
    handle->next = event_listener_list;
    event_listener_list = handle;
    return 0;
}

int event_remove_listener(void *handle)
{
    EventListener **prev = &event_listener_list;
    for (EventListener *iter = event_listener_list; iter; iter = iter->next)
    {
        if (iter == handle)
        {
            *prev = iter->next;
            free_(iter);
            return 0;
        }
        prev = &iter->next;
    }
    fprintf(stderr, "event_remove_listener: listener not found\n");
    return -1;
}

void event_free()
{
    while (event_listener_list)
    {
        EventListener *next = event_listener_list->next;
        free_(event_listener_list);
        event_listener_list = next;
    }
}

int event_broadcast(EventType type, void *event)
{
    for (EventListener *iter = event_listener_list; iter; iter = iter->next)
    {
        int err = iter->listener(type, event, iter->context);
        if (err)
        {
            return err;
        }
    }
    return 0;
}

#endif // CSYNTH_EVENT_H
