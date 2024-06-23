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

typedef enum
{
    KnobTypeNone = 0,
    KnobTypeLinear = 1,
    KnobTypeExponential = 2,
} KnobType;

typedef struct
{
    MidiEventContext parent;
    MidiKey key;
    double value;
    KnobType type;
} KnobContext;

static double knob_eval(__U int count, __U Gen **args, __U double delta, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    double min = gen_eval(args[0]);
    double max = gen_eval(args[1]);
    switch (context->type)
    {
    case KnobTypeNone:
        break;
    case KnobTypeLinear:
        return (max - min) * context->value + min;
    case KnobTypeExponential:
        return pow(max / min, context->value) * min;
    }
    return 0;
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

static int knob_init(__U int count, __U Gen **args, __U double delta, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    state_event_broadcast(StateEventKeyTypeMidi, &context->key, StateEventValueTypeDouble, &context->value);
    csError error = midi_event_add(&context->parent);
    return error_catch(error);
}

Func *knob_direct(int channel, int control, Func *min, Func *max, KnobType type)
{
    KnobContext initial = (KnobContext){
        .parent = {.handle_event = knob_handle_event},
        .key = (MidiKey){
            .channel = channel - 1,
            .control = control,
        },
        .type = type,
    };
    return func_create(knob_init, knob_eval, midi_event_free, sizeof(KnobContext), &initial, FUNC_FLAG_SKIP_RESET, 2, min, max);
}

Func *knob_smooth(int channel, int control, Func *min, Func *max, Func *derivative, KnobType type) { return slope(knob_direct(channel, control, min, max, type), derivative); }

Func *knob(int channel, int index, Func *min, Func *max) { return knob_smooth(channel, index, min, max, const_(1), KnobTypeLinear); }
Func *knob_(int channel, int index, double min, double max) { return knob(channel, index, const_(min), const_(max)); }

Func *knob_exp(int channel, int index, Func *min, Func *max) { return knob_smooth(channel, index, min, max, const_(1), KnobTypeExponential); }
Func *knob_exp_(int channel, int index, double min, double max) { return knob_exp(channel, index, const_(min), const_(max)); }

#endif // CSYNTH_KNOB_H
