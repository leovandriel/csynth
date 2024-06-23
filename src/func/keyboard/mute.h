//
// mute.h - Mute/unmute based on key press
//
#ifndef CSYNTH_MUTE_H
#define CSYNTH_MUTE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/keyboard_event.h"
#include "../../event/state_event.h"

typedef struct
{
    KeyboardEventContext parent;
    int key;
    int muted;
} MuteContext;

static double mute_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    MuteContext *context = (MuteContext *)context_;
    double output = gen_eval(args[0], eval);
    return context->muted ? 0 : output;
}

static void mute_handle_event(int key, void *context_)
{
    MuteContext *context = (MuteContext *)context_;
    if (key == context->key)
    {
        context->muted = !context->muted;
        state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeBoolInv, &context->muted);
    }
}

static int mute_init(__U int count, __U Gen **args, void *context_)
{
    MuteContext *context = (MuteContext *)context_;
    state_event_broadcast(StateEventKeyTypeKeyboard, &context->key, StateEventValueTypeBoolInv, &context->muted);
    csError error = keyboard_event_add(&context->parent);
    return error_catch(error);
}

Func *mute_(int key, Func *func, int muted)
{
    MuteContext initial = {
        .parent = {.handle_event = mute_handle_event},
        .key = key,
        .muted = muted,
    };
    return func_create(mute_init, mute_eval, keyboard_event_free, sizeof(MuteContext), &initial, FuncFlagNone, 1, func);
}

Func *mute(int key, Func *func)
{
    return mute_(key, func, 0);
}

Func *unmute(int key, Func *func)
{
    return mute_(key, func, 1);
}

#endif // CSYNTH_MUTE_H
