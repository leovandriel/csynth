//
// keyboard_event.h - Func lifecyle for key events
//
#ifndef CSYNTH_KEYBOARD_EVENT_H
#define CSYNTH_KEYBOARD_EVENT_H

#include "../core/gen.h"
#include "./event.h"

typedef int (*keyboard_event_listener)(int key, void *context);

#define KEYBOARD_EVENT_UP 1792833
#define KEYBOARD_EVENT_DOWN 1792834

typedef struct
{
    double time;
    int key;
} KeyboardEvent;

typedef struct
{
    void *handle;
    keyboard_event_listener keyboard_listener;
} KeyboardEventContext;

int keyboard_event_broadcast(double time, int key)
{
    KeyboardEvent event = {.time = time, .key = key};
    return event_broadcast(EventTypeKeyboard, &event);
}

int keyboard_event_listen(EventType type, void *event_, void *context_)
{
    KeyboardEventContext *context = (KeyboardEventContext *)context_;
    if (type == EventTypeKeyboard)
    {
        KeyboardEvent *event = (KeyboardEvent *)event_;
        return context->keyboard_listener(event->key, context);
    }
    return 0;
}

void keyboard_event_add(KeyboardEventContext *context)
{
    context->handle = event_add_listener(keyboard_event_listen, context);
}

void keyboard_event_remove(KeyboardEventContext *context)
{
    event_remove_listener(context->handle);
    context->handle = NULL;
}

void keyboard_event_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context)
{
    keyboard_event_add((KeyboardEventContext *)context);
}

void keyboard_event_free(__attribute__((unused)) int count, void *context)
{
    keyboard_event_remove((KeyboardEventContext *)context);
}

#endif // CSYNTH_KEYBOARD_EVENT_H
