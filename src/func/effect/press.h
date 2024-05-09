//
// press.h - Trigger based on key press
//
#ifndef CSYNTH_PRESS_H
#define CSYNTH_PRESS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/event.h"

typedef struct
{
    EventListener *listener;
    char key;
    int active;
    int pressed;
} PressContext;

static double press_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    PressContext *context = (PressContext *)context_;
    if (context->pressed)
    {
        gen_reset(args[0]);
        context->pressed = 0;
    }
    return context->active ? gen_eval(args[0]) : 0;
}

int press_listener(EventType type, void *event, void *context_)
{
    PressContext *context = (PressContext *)context_;
    if (type == EventTypeKey)
    {
        int key = *(int *)event;
        if (key == context->key)
        {
            context->active = 1;
            context->pressed = 1;
        }
    }
    return 0;
}

void press_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    PressContext *context = (PressContext *)context_;
    context->listener = event_add_listener(press_listener, context);
}

void press_free(void *context_)
{
    PressContext *context = (PressContext *)context_;
    event_remove_listener(context->listener);
    context->listener = NULL;
}

Func *press(char key, Func *func)
{
    PressContext initial = (PressContext){
        .key = key,
    };
    return func_create(press_init, press_eval, press_free, sizeof(PressContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
}

#endif // CSYNTH_PRESS_H
