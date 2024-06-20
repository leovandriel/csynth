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
    EventTypeKeyboard = 1,
    EventTypeState = 2,
    EventTypeMidi = 3,
} EventType;

typedef void (*event_handle_event)(EventType type, void *event, void *context);

typedef struct EventHandler
{
    event_handle_event handle_event;
    void *context;
    struct EventHandler *next;
} EventHandler;

EventHandler *event_handler_list = NULL;

void *event_add_handler(event_handle_event handle_event, void *context)
{
    EventHandler *handler = (EventHandler *)malloc_(sizeof(EventHandler));
    if (handler == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    *handler = (EventHandler){.handle_event = handle_event, .context = context, .next = event_handler_list};
    event_handler_list = handler;
    return handler;
}

csError event_remove_handler(void *handler_)
{
    EventHandler **prev = &event_handler_list;
    for (EventHandler *handler = event_handler_list; handler; handler = handler->next)
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
    while (event_handler_list)
    {
        EventHandler *next = event_handler_list->next;
        free_(event_handler_list);
        event_handler_list = next;
    }
}

void event_broadcast(EventType type, void *event)
{
    for (EventHandler *handler = event_handler_list; handler; handler = handler->next)
    {
        handler->handle_event(type, event, handler->context);
    }
}

#endif // CSYNTH_EVENT_H
