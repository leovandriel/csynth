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
#include "../gen/const.h"
#include "../op/mul.h"

typedef struct
{
    MidiEventContext parent;
    MidiKey key;
    double value;
    double target;
    int exponential;
    double min;
    double max;
} KnobContext;

static double knob_eval(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    double min = gen_eval(args[0]);
    double max = gen_eval(args[1]);
    double slope = gen_eval(args[2]) * delta;
    double diff = context->target - context->value;
    if (diff > slope)
    {
        diff = slope;
    }
    if (diff < -slope)
    {
        diff = -slope;
    }
    context->value += diff;
    context->min = min;
    context->max = max;
    if (context->exponential)
    {
        return pow(max / min, context->value) * min;
    }
    return (max - min) * context->value + min;
}

static void knob_listener(__attribute__((unused)) double time, MidiType type, uint8_t channel, uint8_t data1, uint8_t data2, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    if (type == MidiTypeControlChange && channel == context->key.channel && data1 == context->key.control)
    {
        context->target = (double)data2 / 127.0;
        state_event_broadcast(StateEventKeyTypeMidi, &context->key, StateEventValueTypeDouble, &context->target);
    }
}

static int knob_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    state_event_broadcast(StateEventKeyTypeMidi, &context->key, StateEventValueTypeDouble, &context->target);
    csError error = midi_event_add(&context->parent);
    return error_catch(error);
}

Func *knob_diff(int channel, int control, Func *min, Func *max, Func *slope, int exponential)
{
    KnobContext initial = (KnobContext){
        .parent = {.midi_listener = knob_listener},
        .key = (MidiKey){
            .channel = channel - 1,
            .control = control,
        },
        .exponential = exponential,
    };
    return func_create(knob_init, knob_eval, midi_event_free, sizeof(KnobContext), &initial, FUNC_FLAG_SKIP_RESET, 3, min, max, slope);
}

Func *knob(int channel, int index, Func *min, Func *max) { return knob_diff(channel, index, min, max, const_(1), 0); }
Func *knob_(int channel, int index, double min, double max) { return knob(channel, index, const_(min), const_(max)); }

Func *knob_exp(int channel, int index, Func *min, Func *max) { return knob_diff(channel, index, min, max, const_(1), 1); }
Func *knob_exp_(int channel, int index, double min, double max) { return knob_exp(channel, index, const_(min), const_(max)); }

#endif // CSYNTH_KNOB_H
