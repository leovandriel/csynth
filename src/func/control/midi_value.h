#ifndef CSYNTH_MIDI_VALUE_H
#define CSYNTH_MIDI_VALUE_H

#include <float.h>
#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../ui/midi_state.h"

/** @see midi_value_create */
typedef struct
{
    /** @brief MIDI type to get value for. */
    MidiType type;
    /** @brief MIDI channel to get value for. */
    uint8_t channel;
    /** @brief MIDI control number to get value for. */
    uint8_t data1;
} MidiValueContext;

static double midi_value_eval(__U size_t count, __U Gen **args, __U Eval *eval, void *context_)
{
    MidiValueContext *context = (MidiValueContext *)context_;
    return midi_state_get(context->type, context->channel, context->data1);
}

/**
 * @brief Create a function that gets a MIDI control value.
 *
 * @param type MIDI message type.
 * @param channel MIDI channel.
 * @param control MIDI control number.
 * @return Func* Value function.
 */
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
