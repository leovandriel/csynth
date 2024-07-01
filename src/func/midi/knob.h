//
// knob.h - Analog control knob
//
#ifndef CSYNTH_KNOB_H
#define CSYNTH_KNOB_H

#include <float.h>
#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/midi_event.h"
#include "../../event/state_event.h"

typedef struct
{
    MidiEventContext parent;
    MidiKey key;
    double value;
} KnobContext;

static double knob_eval(__U int count, __U Gen **args, __U Eval eval, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    return context->value;
}

static void knob_handle_event(__U double time, MidiType type, uint8_t channel, uint8_t data1, uint8_t data2, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    if (type == MidiTypeControlChange && channel == context->key.channel && data1 == context->key.control)
    {
        context->value = (double)data2 / 127.0;
        state_event_broadcast(StateEventKeyTypeMidi, &context->key, StateEventValueTypeDouble, &context->value);
    }
}

static int knob_init(__U int count, __U Gen **args, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    state_event_broadcast(StateEventKeyTypeMidi, &context->key, StateEventValueTypeDouble, &context->value);
    csError error = midi_event_add(&context->parent);
    return error_catch(error);
}

Func *knob_create(int channel, int control)
{
    KnobContext initial = {
        .parent = {.handle_event = knob_handle_event},
        .key = {
            .channel = channel - 1,
            .control = control,
        },
    };
    return func_create(knob_init, knob_eval, midi_event_free, sizeof(KnobContext), &initial, FuncFlagSkipReset, FUNCS());
}

#endif // CSYNTH_KNOB_H
