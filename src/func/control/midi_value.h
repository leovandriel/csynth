//
// midi_value.h - Get MIDI control value
//
#ifndef CSYNTH_MIDI_VALUE_H
#define CSYNTH_MIDI_VALUE_H

#include <float.h>
#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../ui/midi_state.h"

typedef struct
{
    MidiType type;
    uint8_t channel;
    uint8_t data1;
} MidiValueContext;

static double midi_value_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    MidiValueContext *context = (MidiValueContext *)context_;
    return midi_state_get(context->type, context->channel, context->data1);
}

Func *midi_value_create(MidiType type, int channel, int control)
{
    MidiValueContext initial = {
        .type = type,
        .channel = channel - 1,
        .data1 = control,
    };
    return func_create(NULL, midi_value_eval, NULL, sizeof(MidiValueContext), &initial, FuncFlagSkipReset, );
}

#endif // CSYNTH_MIDI_VALUE_H
