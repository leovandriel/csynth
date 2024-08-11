#ifndef CSYNTH_PAUSE_H
#define CSYNTH_PAUSE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"

/** @see pause_create */
typedef struct
{
    /** @brief Super struct, allowing use of control_event_free. */
    ControlEventContext parent;
    /** @brief Key to pause/play. */
    ControlEventKey key;
    /** @brief Flag to indicate if paused. */
    bool paused;
    /** @brief Flag to reset function. */
    bool reset;
    /** @brief Flag to configure resetting on/off. */
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

static int pause_init(__U size_t count, __U Gen **args, void *context_)
{
    PauseContext *context = (PauseContext *)context_;
    state_event_broadcast(0, StateEventKeyTypeControl, &context->key, StateEventValueTypeBool, &context->paused);
    return control_event_add(&context->parent);
}

/**
 * @brief Create function to pause/unpause based on key stroke.
 *
 * @param key Key index to listen for.
 * @param play_reset Reset input on play.
 * @param paused Initial pause state.
 * @param input Input function to pause/unpause.
 * @return Func* Pause function.
 */
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
    return func_create(pause_init, pause_eval, control_event_free, NULL, sizeof(PauseContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_PAUSE_H
