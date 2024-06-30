//
// midis.h - Misc midi controls
//
#ifndef CSYNTH_MIDIS_H
#define CSYNTH_MIDIS_H

#include <math.h>

#include "../../core/func.h"
#include "../../util/error.h"
#include "../gen/gens.h"
#include "../gen/notes.h"
#include "../op/add.h"
#include "../op/mul.h"

#define MIDI_NOTE_COUNT 0x80

typedef Func *(*midi_control_func)(int channel, int key, Func *input);

Func *midi_keyboard(int channel, midi_control_func control, Func *input)
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
    Func *output = add_array(MIDI_NOTE_COUNT, array);
    free_(array);
    return output;
}

#endif // CSYNTH_MIDIS_H
