//
// keyboard_event.h - Func lifecyle for key events
//
#ifndef CSYNTH_KEYBOARD_EVENT_H
#define CSYNTH_KEYBOARD_EVENT_H

#include "../core/gen.h"
#include "./event.h"

typedef void (*keyboard_event_listener)(int key, void *context);

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

void keyboard_event_broadcast(double time, int key)
{
    KeyboardEvent event = {.time = time, .key = key};
    event_broadcast(EventTypeKeyboard, &event);
}

void keyboard_event_listen(EventType type, void *event_, void *context_)
{
    KeyboardEventContext *context = (KeyboardEventContext *)context_;
    if (type == EventTypeKeyboard)
    {
        KeyboardEvent *event = (KeyboardEvent *)event_;
        context->keyboard_listener(event->key, context);
    }
}

csError keyboard_event_add(KeyboardEventContext *context)
{
    void *handle = event_add_listener(keyboard_event_listen, context);
    if (handle == NULL)
    {
        return error_type_message(csErrorInit, "Unable to add keyboard event listener");
    }
    context->handle = handle;
    return csErrorNone;
}

csError keyboard_event_remove(KeyboardEventContext *context)
{
    csError error = event_remove_listener(context->handle);
    if (error != csErrorNone)
    {
        return error;
    }
    context->handle = NULL;
    return csErrorNone;
}

csError keyboard_event_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context)
{
    return keyboard_event_add((KeyboardEventContext *)context);
}

void keyboard_event_free(__attribute__((unused)) int count, void *context)
{
    csError error = keyboard_event_remove((KeyboardEventContext *)context);
    error_catch(error);
}

#endif // CSYNTH_KEYBOARD_EVENT_H
