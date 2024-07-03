//
// event.h - Manage event handlers
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
    EventTypeControl = 1,
    EventTypeState = 2
} EventType;

typedef void (*event_handle_event)(EventType type, const void *event, void *context);

typedef struct EventHandler
{
    event_handle_event handle_event;
    void *context;
    struct EventHandler *next;
} EventHandler;

static EventHandler *event_list_global = NULL;

const void *event_add_handler(event_handle_event handle_event, void *context)
{
    EventHandler *handler = (EventHandler *)malloc_(sizeof(EventHandler));
    if (handler == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    *handler = (EventHandler){
        .handle_event = handle_event,
        .context = context,
        .next = event_list_global,
    };
    event_list_global = handler;
    return handler;
}

csError event_remove_handler(const void *handler_)
{
    EventHandler **prev = &event_list_global;
    for (EventHandler *handler = event_list_global; handler; handler = handler->next)
    {
        if (handler == handler_)
        {
            *prev = handler->next;
            free_(handler);
            return csErrorNone;
        }
        prev = &handler->next;
    }
    return error_type_message(csErrorNotFound, "Event handler not found");
}

void event_clear()
{
    while (event_list_global)
    {
        EventHandler *next = event_list_global->next;
        free_(event_list_global);
        event_list_global = next;
    }
}

void event_broadcast(EventType type, const void *event)
{
    for (EventHandler *handler = event_list_global; handler; handler = handler->next)
    {
        handler->handle_event(type, event, handler->context);
    }
}

size_t event_list_size()
{
    size_t size = 0;
    for (EventHandler *handler = event_list_global; handler; handler = handler->next)
    {
        size++;
    }
    return size;
}

#endif // CSYNTH_EVENT_H
