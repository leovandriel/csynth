//
// key_event.h - Func lifecyle for key events
//
#ifndef CSYNTH_KEY_EVENT_H
#define CSYNTH_KEY_EVENT_H

#include "../core/gen.h"
#include "./event.h"

typedef int (*key_event_listener)(int key, void *context);

#define KEY_EVENT_UP 1792833
#define KEY_EVENT_DOWN 1792834

typedef struct
{
    int key;
} KeyEvent;

typedef struct
{
    void *handle;
    key_event_listener key_listener;
} KeyEventContext;

int key_event_broadcast(int key)
{
    KeyEvent event = {.key = key};
    return event_broadcast(EventTypeKey, &event);
}

int key_event_listen(EventType type, void *event_, void *context_)
{
    KeyEventContext *context = (KeyEventContext *)context_;
    if (type == EventTypeKey)
    {
        KeyEvent *event = (KeyEvent *)event_;
        return context->key_listener(event->key, context);
    }
    return 0;
}

void key_event_add(KeyEventContext *context)
{
    context->handle = event_add_listener(key_event_listen, context);
}

void key_event_remove(KeyEventContext *context)
{
    event_remove_listener(context->handle);
    context->handle = NULL;
}

void key_event_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context)
{
    key_event_add((KeyEventContext *)context);
}

void key_event_free(__attribute__((unused)) int count, void *context)
{
    key_event_remove((KeyEventContext *)context);
}

#endif // CSYNTH_KEY_EVENT_H
