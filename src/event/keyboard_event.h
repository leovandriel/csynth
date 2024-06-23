//
// keyboard_event.h - Func lifecyle for key events
//
#ifndef CSYNTH_KEYBOARD_EVENT_H
#define CSYNTH_KEYBOARD_EVENT_H

#include "../core/gen.h"
#include "./event.h"

typedef void (*keyboard_handle_event)(int key, void *context);

#define KEYBOARD_EVENT_UP 1792833
#define KEYBOARD_EVENT_DOWN 1792834

typedef struct
{
    double time;
    int key;
} KeyboardEvent;

typedef struct
{
    const void *handler;
    keyboard_handle_event handle_event;
} KeyboardEventContext;

void keyboard_event_broadcast(double time, int key)
{
    KeyboardEvent event = {.time = time, .key = key};
    event_broadcast(EventTypeKeyboard, &event);
}

void keyboard_handle_event_(EventType type, const void *event_, void *context_)
{
    KeyboardEventContext *context = (KeyboardEventContext *)context_;
    if (type == EventTypeKeyboard)
    {
        KeyboardEvent *event = (KeyboardEvent *)event_;
        context->handle_event(event->key, context);
    }
}

csError keyboard_event_add(KeyboardEventContext *context)
{
    const void *handler = event_add_handler(keyboard_handle_event_, context);
    if (handler == NULL)
    {
        return error_type_message(csErrorInit, "Unable to add keyboard event handler");
    }
    context->handler = handler;
    return csErrorNone;
}

csError keyboard_event_remove(KeyboardEventContext *context)
{
    csError error = event_remove_handler(context->handler);
    if (error != csErrorNone)
    {
        return error;
    }
    context->handler = NULL;
    return csErrorNone;
}

csError keyboard_event_init(__U int count, __U Gen **args, void *context)
{
    return keyboard_event_add((KeyboardEventContext *)context);
}

void keyboard_event_free(__U int count, void *context)
{
    csError error = keyboard_event_remove((KeyboardEventContext *)context);
    error_catch(error);
}

#endif // CSYNTH_KEYBOARD_EVENT_H
