//
// pause.h - Pause/play based on key press
//
#ifndef CSYNTH_PAUSE_H
#define CSYNTH_PAUSE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/key_event.h"
#include "../../event/state_event.h"

typedef struct
{
    KeyEventContext parent;
    int key;
    int paused;
    int reset;
    int play_reset;
} PauseContext;

static double pause_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    if (context->reset)
    {
        gen_reset(args[0]);
        context->reset = 0;
    }
    return context->paused ? 0 : gen_eval(args[0]);
}

int pause_listener(int key, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    if (key == context->key)
    {
        context->paused = !context->paused;
        context->reset = context->play_reset;
        state_event_broadcast(context->key, StateEventTypeBool, &context->paused);
    }
    return 0;
}

void pause_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    state_event_broadcast(context->key, StateEventTypeBool, &context->paused);
    key_event_add(&context->parent);
}

Func *pause_play_(int key, Func *func, int play_reset, int paused)
{
    PauseContext initial = (PauseContext){
        .parent = {.key_listener = pause_listener},
        .key = key,
        .play_reset = play_reset,
        .paused = paused,
    };
    return func_create(pause_init, pause_eval, key_event_free, sizeof(PauseContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
}

Func *pause_play(int key, Func *func)
{
    return pause_play_(key, func, 0, 0);
}

Func *play_pause(int key, Func *func)
{
    return pause_play_(key, func, 0, 1);
}

Func *pause_reset(int key, Func *func)
{
    return pause_play_(key, func, 1, 0);
}

Func *reset_pause(int key, Func *func)
{
    return pause_play_(key, func, 1, 1);
}

#endif // CSYNTH_PAUSE_H
