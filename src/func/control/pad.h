#ifndef CSYNTH_PAD_H
#define CSYNTH_PAD_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"

/** @see pad_create */
typedef struct
{
    /** @brief Super struct, allowing use of control_event_free. */
    ControlEventContext parent;
    /** @brief Key to trigger the input. */
    ControlEventKey key;
    /** @brief Velocity of the pad activation, i.e. gain. */
    double value;
    /** @brief Flag to reset function. */
    bool reset;
} PadContext;

static double pad_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    PadContext *context = (PadContext *)context_;
    if (context->reset)
    {
        gen_reset(args[0]);
        context->reset = false;
    }
    double input = gen_eval(args[0], eval);
    return input * context->value;
}

static void pad_handle_event(ControlEvent *event, void *context_)
{
    PadContext *context = (PadContext *)context_;
    if (control_event_key_equal(event->key, context->key) && event->key.midi.type == MidiTypeNoteOn)
    {
        context->value = (double)event->key.midi.data2 / 127.0;
        context->reset = true;
    }
}

static int pad_init(__U size_t count, __U Gen **args, void *context_)
{
    PadContext *context = (PadContext *)context_;
    return control_event_add(&context->parent);
}

/**
 * @brief Create a function that triggers an input function with a MIDI pad.
 *
 * @param channel MIDI channel of the pad.
 * @param pad MIDI pad number.
 * @param input Input function to trigger.
 * @return Func* Pad function.
 */
Func *pad_create(int channel, int pad, Func *input)
{
    PadContext initial = {
        .parent = {.handle_event = pad_handle_event},
        .key = {
            .type = ControlEventTypeMidi,
            .midi = {
                .type = MidiTypeNoteOn,
                .channel = channel - 1,
                .data1 = pad,
            },
        }};
    return func_create(pad_init, pad_eval, control_event_free, NULL, sizeof(PadContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_PAD_H
