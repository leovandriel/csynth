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

static double pause_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    if (context->reset != 0)
    {
        gen_reset(args[0]);
        context->reset = 0;
    }
    return context->paused ? 0 : gen_eval(args[0], eval);
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

static int pause_init(__U int count, __U Gen **args, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeBool, &context->paused);
    csError error = keyboard_event_add(&context->parent);
    return error_catch(error);
}

Func *pause_create(int key, int play_reset, int paused, Func *input)
{
    PauseContext initial = {
        .parent = {.handle_event = pause_handle_event},
        .key = key,
        .play_reset = play_reset,
        .paused = paused,
    };
    return func_create(pause_init, pause_eval, keyboard_event_free, sizeof(PauseContext), &initial, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_PAUSE_H
