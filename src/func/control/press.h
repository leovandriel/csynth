//
// press.h - Trigger based on key press
//
#ifndef CSYNTH_PRESS_H
#define CSYNTH_PRESS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/key_event.h"
#include "../../event/state_event.h"

typedef struct
{
    KeyEventContext parent;
    int key;
    int pressed;
    int reset;
} PressContext;

static double press_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    PressContext *context = (PressContext *)context_;
    if (context->reset)
    {
        gen_reset(args[0]);
        context->reset = 0;
    }
    return context->pressed ? gen_eval(args[0]) : 0;
}

int press_listener(int key, void *context_)
{
    PressContext *context = (PressContext *)context_;
    if (key == context->key)
    {
        context->pressed = 1;
        context->reset = 1;
        state_event_broadcast(context->key, StateEventTypeTrigger, &context->pressed);
    }
    return 0;
}

void press_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    PressContext *context = (PressContext *)context_;
    state_event_broadcast(context->key, StateEventTypeTrigger, &context->pressed);
    key_event_add(&context->parent);
}

Func *press(int key, Func *func)
{
    PressContext initial = (PressContext){
        .parent = {.key_listener = press_listener},
        .key = key,
    };
    return func_create(press_init, press_eval, key_event_free, sizeof(PressContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
}

#endif // CSYNTH_PRESS_H
