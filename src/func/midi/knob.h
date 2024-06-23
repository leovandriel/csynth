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
#include "../filter/slope.h"
#include "../gen/const.h"
#include "../op/mul.h"
#include "../op/ops.h"

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

Func *knob_ctrl(int channel, int control)
{
    KnobContext initial = (KnobContext){
        .parent = {.handle_event = knob_handle_event},
        .key = (MidiKey){
            .channel = channel - 1,
            .control = control,
        },
    };
    return func_create(knob_init, knob_eval, midi_event_free, sizeof(KnobContext), &initial, FuncFlagSkipReset, 0);
}

Func *knob_smooth(int channel, int control, Func *derivative) { return slope(knob_ctrl(channel, control), derivative); }

Func *knob(int channel, int control, Func *min, Func *max) { return linear_op(knob_smooth(channel, control, const_(1)), min, max, const_(1)); }
Func *knob_(int channel, int control, double min, double max) { return knob(channel, control, const_(min), const_(max)); }

Func *knob_ex(int channel, int control, Func *min, Func *max) { return exponent_op(knob_smooth(channel, control, const_(1)), min, max, const_(1)); }
Func *knob_ex_(int channel, int control, double min, double max) { return knob_ex(channel, control, const_(min), const_(max)); }

#endif // CSYNTH_KNOB_H
