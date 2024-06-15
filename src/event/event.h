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
        int capacity = list->capacity ? list->capacity * 2 : 16;
        EventListener **listeners = (EventListener **)realloc_(list->listeners, capacity * sizeof(EventListener *));
        if (!listeners)
        {
            fprintf(stderr, "Failed to allocate memory for event listeners\n");
            return NULL;
        }
        list->capacity = capacity;
        list->listeners = listeners;
    }
    EventListener *handle = (EventListener *)calloc_(1, sizeof(EventListener));
    handle->listener = listener;
    handle->context = context;
    list->listeners[list->size++] = handle;
    return handle;
}

void event_free()
{
    EventListenerList *list = &event_listener_list;
    for (int i = 0; i < list->size; i++)
    {
        free_(list->listeners[i]);
    }
    free_(list->listeners);
    list->listeners = NULL;
    list->capacity = 0;
    list->size = 0;
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
    free_(handle);
}

int event_broadcast(EventType type, void *event)
{
    EventListenerList *list = &event_listener_list;
    for (int i = 0; i < list->size; i++)
    {
        EventListener *listener = list->listeners[i];
        int err = listener->listener(type, event, listener->context);
        if (err)
        {
            return err;
        }
    }
    return 0;
}

#endif // CSYNTH_EVENT_H
