//
// event.h - Manage event listeners
//
#ifndef CSYNTH_EVENT_H
#define CSYNTH_EVENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    EventTypeNone = 0,
    EventTypeKey = 1,
    EventTypeState = 2,
} EventType;

typedef int (*event_listener)(EventType type, void *event, void *context);
typedef struct
{
    event_listener listener;
    void *context;
} EventListener;

typedef struct
{
    EventListener **listeners;
    int capacity;
    int size;
} EventListenerList;

EventListenerList event_listener_list = {0};

void *event_add_listener(event_listener listener, void *context)
{
    EventListenerList *list = &event_listener_list;
    if (list->size == list->capacity)
    {
        list->capacity = list->capacity ? list->capacity * 2 : 16;
        list->listeners = (EventListener **)realloc(list->listeners, list->capacity * sizeof(EventListener *));
    }
    EventListener *handle = (EventListener *)calloc(1, sizeof(EventListener));
    handle->listener = listener;
    handle->context = context;
    list->listeners[list->size++] = handle;
    return handle;
}

void event_remove_listener(void *handle)
{
    EventListenerList *list = &event_listener_list;
    int index = 0;
    for (; index < list->size; index++)
    {
        if (list->listeners[index] == handle)
        {
            break;
        }
    }
    if (index == list->size)
    {
        fprintf(stderr, "event_remove_listener: listener not found\n");
        return;
    }
    list->listeners[index] = list->listeners[list->size-- - 1];
    free(handle);
}

int event_broadcast(EventType type, void *event)
{
    EventListenerList *list = &event_listener_list;
    for (int i = 0; i < list->size; i++)
    {
        EventListener *listener = list->listeners[i];
        int err = listener->listener(type, event, listener->context);
        if (err)
            return err;
    }
    return 0;
}

#endif // CSYNTH_EVENT_H
