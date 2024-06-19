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
    uint32_t index;
    uint32_t channel;
    double value;
    double target;
    int exponential;
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
    if (context->exponential)
    {
        return pow(max / min, context->value) * min;
    }
    return (max - min) * context->value + min;
}

static void knob_listener(__attribute__((unused)) double time, MidiType type, uint32_t channel, uint32_t data1, uint32_t data2, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    if (type == MidiTypeControlChange && channel == context->channel && data1 == context->index)
    {
        context->target = (double)data2 / 127.0;
        state_event_broadcast((int)context->index, StateEventTypeDouble, &context->target);
    }
}

static int knob_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    state_event_broadcast((int)context->index, StateEventTypeDouble, &context->target);
    csError error = midi_event_add(&context->parent);
    return error_catch(error);
}

Func *knob_diff(int index, Func *min, Func *max, Func *slope, int exponential)
{
    KnobContext initial = (KnobContext){
        .parent = {.midi_listener = knob_listener},
        .index = index,
        .exponential = exponential,
    };
    return func_create(knob_init, knob_eval, midi_event_free, sizeof(KnobContext), &initial, FUNC_FLAG_SKIP_RESET, 3, min, max, slope);
}

Func *knob(int index, Func *min, Func *max) { return knob_diff(index, min, max, const_(1), 0); }
Func *knob_(int index, double min, double max) { return knob(index, const_(min), const_(max)); }

Func *knob_exp(int index, Func *min, Func *max) { return knob_diff(index, min, max, const_(1), 1); }
Func *knob_exp_(int index, double min, double max) { return knob_exp(index, const_(min), const_(max)); }

#endif // CSYNTH_KNOB_H
