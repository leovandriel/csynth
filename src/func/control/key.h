#ifndef CSYNTH_KEY_H
#define CSYNTH_KEY_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"

/** @see key_create */
typedef struct
{
    /** @brief Super struct, allowing use of control_event_free. */
    ControlEventContext parent;
    /** @brief Key to trigger. */
    ControlEventKey key;
    /** @brief Flag to indicate if key is active. */
    bool active;
    /** @brief Flag to indicate function reset. */
    bool reset;
} KeyContext;

static double key_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    if (context->reset)
    {
        gen_reset(args[0]);
        context->reset = false;
    }
    if (context->active)
    {
        double input = gen_eval(args[0], eval);
        return input * (double)context->active / 64.0;
    }
    return 0.;
}

static void key_handle_event(ControlEvent *event, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    if (control_event_key_equal(event->key, context->key))
    {
        context->active = event->key.midi.data2 != 0;
        context->reset = event->key.midi.data2 != 0;
    }
}

static bool key_init(__U size_t count, __U Gen **args, void *context_)
{
    KeyContext *context = (KeyContext *)context_;
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

/**
 * @brief Trigger based on MIDI key press.
 *
 * @param channel The MIDI channel.
 * @param pitch The MIDI key pitch.
 * @param input The input function to sample after trigger.
 * @return Func* Key function.
 */
Func *key_create(int channel, int pitch, Func *input)
{
    KeyContext initial = {
        .parent = {.handle_event = key_handle_event},
        .key = {
            .type = ControlEventTypeMidi,
            .midi = {
                .type = MidiTypeNoteOff,
                .channel = channel - 1,
                .data1 = pitch,
            }},
    };
    return func_create(key_init, key_eval, control_event_free, sizeof(KeyContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_KEY_H
