//
// midi_keyboard.h - MIDI keyboard controls
//
#ifndef CSYNTH_MIDI_KEYBOARD_H
#define CSYNTH_MIDI_KEYBOARD_H

#include <math.h>

#include "../../core/func.h"
#include "../../ui/midi_state.h"
#include "../../util/error.h"
#include "../op/add.h"
#include "../time/times.h"

typedef Func *(*midi_control_func)(int channel, int key, Func *input);

Func *midi_keyboard(int channel, midi_control_func control, Func *input) /* midi_keyboard_ */
{
    Func **array = (Func **)malloc_(MIDI_NOTE_COUNT * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    for (int i = 0; i < MIDI_NOTE_COUNT; i++)
    {
        Func *pitched = pitch_(exp2(i / 12.0), input);
        array[i] = control(channel, i, pitched);
    }
    Func *output = add_create(MIDI_NOTE_COUNT, array);
    free_(array);
    return output;
}

#endif // CSYNTH_MIDI_KEYBOARD_H
