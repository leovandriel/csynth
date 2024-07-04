//
// pad.h - Trigger based on pad
//
#ifndef CSYNTH_PAD_H
#define CSYNTH_PAD_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"

typedef struct
{
    ControlEventContext parent;
    ControlEventKey key;
    double value;
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

static bool pad_init(__U size_t count, __U Gen **args, void *context_)
{
    PadContext *context = (PadContext *)context_;
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

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
    return func_create(pad_init, pad_eval, control_event_free, sizeof(PadContext), &initial, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_PAD_H
