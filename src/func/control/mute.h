//
// mute.h - Pause/play based on key press
//
#ifndef CSYNTH_MUTE_H
#define CSYNTH_MUTE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/key_event.h"
#include "../../event/state_event.h"

typedef struct
{
    KeyEventContext parent;
    int key;
    int muted;
} MuteContext;

static double mute_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    MuteContext *context = (MuteContext *)context_;
    double output = gen_eval(args[0]);
    return context->muted ? 0 : output;
}

int mute_listener(int key, void *context_)
{
    MuteContext *context = (MuteContext *)context_;
    if (key == context->key)
    {
        context->muted = !context->muted;
        state_event_broadcast(context->key, StateEventTypeBoolInv, &context->muted);
    }
    return 0;
}

void mute_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    MuteContext *context = (MuteContext *)context_;
    state_event_broadcast(context->key, StateEventTypeBoolInv, &context->muted);
    key_event_add(&context->parent);
}

Func *mute_(int key, Func *func, int muted)
{
    MuteContext initial = (MuteContext){
        .parent = {.key_listener = mute_listener},
        .key = key,
        .muted = muted,
    };
    return func_create(mute_init, mute_eval, key_event_free, sizeof(MuteContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
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
