//
// knob.h - Analog control knob
//
#ifndef CSYNTH_KNOB_H
#define CSYNTH_KNOB_H

#include <float.h>
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
} KnobContext;

static double knob_eval(__U int count, __U Gen **args, __U EvalContext *eval, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    return context->value;
}

static void knob_handle_event(ControlEvent *event, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    if (control_event_key_equal(event->key, context->key))
    {
        context->value = (double)event->key.midi.data2 / 127.0;
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeDouble, &context->value);
    }
}

static int knob_init(__U int count, __U Gen **args, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    state_event_broadcast(0, StateEventKeyTypeControl, &context->key, StateEventValueTypeDouble, &context->value);
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

Func *knob_create(int channel, int control)
{
    KnobContext initial = {
        .parent = {.handle_event = knob_handle_event},
        .key = {
            .type = ControlEventTypeMidi,
            .midi = {
                .type = MidiTypeController,
                .channel = channel - 1,
                .data1 = control,
            }},
    };
    return func_create(knob_init, knob_eval, control_event_free, sizeof(KnobContext), &initial, FuncFlagSkipReset, FUNCS());
}

#endif // CSYNTH_KNOB_H
