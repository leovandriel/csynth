//
// pause.h - Pause/play based on key press
//
#ifndef CSYNTH_PAUSE_H
#define CSYNTH_PAUSE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/keyboard_event.h"
#include "../../event/state_event.h"

typedef struct
{
    KeyboardEventContext parent;
    int key;
    int paused;
    int reset;
    int play_reset;
} PauseContext;

static double pause_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    if (context->reset != 0)
    {
        gen_reset(args[0]);
        context->reset = 0;
    }
    return context->paused ? 0 : gen_eval(args[0]);
}

static void pause_handle_event(int key, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    if (key == context->key)
    {
        context->paused = !context->paused;
        context->reset = context->play_reset;
        state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeBool, &context->paused);
    }
}

static int pause_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeBool, &context->paused);
    csError error = keyboard_event_add(&context->parent);
    return error_catch(error);
}

Func *pause_play_(int key, Func *func, int play_reset, int paused)
{
    PauseContext initial = (PauseContext){
        .parent = {.handle_event = pause_handle_event},
        .key = key,
        .play_reset = play_reset,
        .paused = paused,
    };
    return func_create(pause_init, pause_eval, keyboard_event_free, sizeof(PauseContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
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
