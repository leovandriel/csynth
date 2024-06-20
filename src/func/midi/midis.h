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

#define MIDI_NOTE_COUNT 100

typedef Func *(*midi_control_func)(int channel, int key, Func *frequency);

Func *midi_keyboard(int channel, midi_control_func control, gen_func generator, Func *frequency)
{
    Func **array = (Func **)malloc_(MIDI_NOTE_COUNT * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    for (int i = 0; i < MIDI_NOTE_COUNT; i++)
    {
        Func *gen = generator(mul_(frequency, pow(2, i / 12.0)));
        array[i] = control(channel, i, gen);
    }
    Func *func = add_array(MIDI_NOTE_COUNT, array);
    free_(array);
    return func;
}

Func *midi_keyboard_(int channel, midi_control_func control, gen_func generator, double frequency)
{
    return midi_keyboard(channel, control, generator, const_(frequency));
}

#endif // CSYNTH_MIDIS_H
