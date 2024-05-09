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

void event_extend_list(EventListenerList *list)
{
    int capacity = list->capacity ? list->capacity * 2 : 16;
    EventListener **listeners = (EventListener **)calloc(capacity, sizeof(EventListener *));
    memcpy(listeners, list->listeners, list->capacity * sizeof(EventListener *));
    free(list->listeners);
    list->listeners = listeners;
    list->capacity = capacity;
}

EventListener *event_add_listener(event_listener listener, void *context)
{
    if (event_listener_list.size == event_listener_list.capacity)
    {
        event_extend_list(&event_listener_list);
    }
    EventListener *event_listener = (EventListener *)calloc(1, sizeof(EventListener));
    event_listener->listener = listener;
    event_listener->context = context;
    event_listener_list.listeners[event_listener_list.size++] = event_listener;
    return event_listener;
}

void event_remove_listener(EventListener *listener)
{
    int index = 0;
    for (; index < event_listener_list.size; index++)
    {
        if (event_listener_list.listeners[index] == listener)
        {
            break;
        }
    }
    if (index == event_listener_list.size)
    {
        fprintf(stderr, "event_remove_listener: listener not found\n");
        return;
    }
    event_listener_list.listeners[index] = event_listener_list.listeners[event_listener_list.size-- - 1];
    free(listener);
}

int event_broadcast(EventType type, void *event)
{
    for (int i = 0; i < event_listener_list.size; i++)
    {
        EventListener *listener = event_listener_list.listeners[i];
        int err = listener->listener(type, event, listener->context);
        if (err)
            return err;
    }
    return 0;
}

#endif // CSYNTH_EVENT_H
