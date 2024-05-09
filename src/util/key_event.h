//
// key_event.h - Func lifecyle for key events
//
#ifndef CSYNTH_KEY_EVENT_H
#define CSYNTH_KEY_EVENT_H

#include "../core/gen.h"
#include "./event.h"

typedef int (*key_event_listener)(int key, void *context);

typedef struct
{
    EventListener *listener;
    key_event_listener key_listener;
} KeyEventContext;

int key_event_listen(EventType type, void *event, void *context_)
{
    KeyEventContext *context = (KeyEventContext *)context_;
    if (type == EventTypeKey)
    {
        int key = *(int *)event;
        context->key_listener(key, context);
    }
    return 0;
}

void key_event_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    KeyEventContext *context = (KeyEventContext *)context_;
    context->listener = event_add_listener(key_event_listen, context);
}

void key_event_free(void *context_)
{
    KeyEventContext *context = (KeyEventContext *)context_;
    event_remove_listener(context->listener);
    context->listener = NULL;
}

#endif // CSYNTH_KEY_EVENT_H
