//
// pause.h - Pause/play based on key press
//
#ifndef CSYNTH_PAUSE_H
#define CSYNTH_PAUSE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"

typedef struct
{
    ControlEventContext parent;
    ControlEventKey key;
    bool paused;
    bool reset;
    bool play_reset;
} PauseContext;

static double pause_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    if (context->reset)
    {
        gen_reset(args[0]);
        context->reset = false;
    }
    return context->paused ? 0 : gen_eval(args[0], eval);
}

static void pause_handle_event(ControlEvent *event, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    if (control_event_key_equal(event->key, context->key))
    {
        context->paused = !context->paused;
        context->reset = context->play_reset;
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeBool, &context->paused);
    }
}

static bool pause_init(__U size_t count, __U Gen **args, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    state_event_broadcast(0, StateEventKeyTypeControl, &context->key, StateEventValueTypeBool, &context->paused);
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

Func *pause_create(int key, bool play_reset, bool paused, Func *input)
{
    PauseContext initial = {
        .parent = {.handle_event = pause_handle_event},
        .key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        },
        .play_reset = play_reset,
        .paused = paused,
    };
    return func_create(pause_init, pause_eval, control_event_free, sizeof(PauseContext), &initial, FuncFlagNone, ARGS(input));
}

#endif // CSYNTH_PAUSE_H
