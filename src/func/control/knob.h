//
// knob.h - Analog control knob
//
#ifndef CSYNTH_KNOB_H
#define CSYNTH_KNOB_H

#include <float.h>
#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../ui/midi_state.h"

typedef struct
{
    uint8_t channel;
    uint8_t data1;
} KnobContext;

static double knob_eval(__U int count, __U Gen **args, __U Eval *eval, void *context_)
{
    KnobContext *context = (KnobContext *)context_;
    double value = midi_state_get(MidiTypeController, context->channel, context->data1);
    return value;
}

Func *knob_create(int channel, int control)
{
    KnobContext initial = {
        .channel = channel - 1,
        .data1 = control,
    };
    return func_create(NULL, knob_eval, NULL, sizeof(KnobContext), &initial, FuncFlagSkipReset, FUNCS());
}

#endif // CSYNTH_KNOB_H
