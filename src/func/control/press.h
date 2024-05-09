//
// press.h - Trigger based on key press
//
#ifndef CSYNTH_PRESS_H
#define CSYNTH_PRESS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/key_event.h"

typedef struct
{
    KeyEventContext parent;
    char key;
    int active;
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
    return context->active ? gen_eval(args[0]) : 0;
}

int press_listener(int key, void *context_)
{
    PressContext *context = (PressContext *)context_;
    if (key == context->key)
    {
        context->active = 1;
        context->reset = 1;
    }
    return 0;
}

Func *press(char key, Func *func)
{
    PressContext initial = (PressContext){
        .parent = {.key_listener = press_listener},
        .key = key,
    };
    return func_create(key_event_init, press_eval, key_event_free, sizeof(PressContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
}

#endif // CSYNTH_PRESS_H
