//
// mute.h - Mute/unmute based on key press
//
#ifndef CSYNTH_MUTE_H
#define CSYNTH_MUTE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"

typedef struct
{
    ControlEventContext parent;
    ControlEventKey key;
    int muted;
} MuteContext;

static double mute_eval(__U int count, __U Gen **args, Eval eval, void *context_)
{
    MuteContext *context = (MuteContext *)context_;
    double input = gen_eval(args[0], eval);
    return context->muted ? 0 : input;
}

static void mute_handle_event(ControlEvent event, void *context_)
{
    MuteContext *context = (MuteContext *)context_;
    if (control_event_key_equal(event.key, context->key))
    {
        context->muted = !context->muted;
        state_event_broadcast(StateEventKeyTypeControl, &context->key, StateEventValueTypeBoolInv, &context->muted);
    }
}

static int mute_init(__U int count, __U Gen **args, void *context_)
{
    MuteContext *context = (MuteContext *)context_;
    state_event_broadcast(StateEventKeyTypeControl, &context->key, StateEventValueTypeBoolInv, &context->muted);
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

Func *mute_create(int key, int muted, Func *input)
{
    MuteContext initial = {
        .parent = {.handle_event = mute_handle_event},
        .key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        },
        .muted = muted,
    };
    return func_create(mute_init, mute_eval, control_event_free, sizeof(MuteContext), &initial, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_MUTE_H
