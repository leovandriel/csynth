//
// midis.h - Misc midi controls
//
#ifndef CSYNTH_MIDIS_H
#define CSYNTH_MIDIS_H

#include <math.h>

#include "../../core/func.h"
#include "../../util/error.h"
#include "../filter/filters.h"
#include "../gen/gens.h"
#include "../op/ops.h"
#include "./blend.h"
#include "./key.h"
#include "./knob.h"
#include "./pad.h"

#define MIDI_NOTE_COUNT 0x80

Func *knob_smooth(int channel, int control, Func *derivative) { return slope(derivative, knob_create(channel, control)); }
Func *knob(int channel, int control, Func *min, Func *max) { return linear_op(const_(1), min, max, knob_smooth(channel, control, const_(1))); }
Func *knob_(int channel, int control, double min, double max) { return knob(channel, control, const_(min), const_(max)); }
Func *knob_ex(int channel, int control, Func *min, Func *max) { return exponent_op(const_(1), min, max, knob_smooth(channel, control, const_(1))); }
Func *knob_ex_(int channel, int control, double min, double max) { return knob_ex(channel, control, const_(min), const_(max)); }

Func *key(int channel, int pitch, Func *input) { return key_create(channel, pitch, input); }
Func *pad(int channel, int pad, Func *input) { return pad_create(channel, pad, input); }
Func *blend(int channel, Func *factor, Func *input) { return blend_create(channel, factor, input); }
Func *blend_(int channel, double factor, Func *input) { return blend(channel, const_(factor), input); }

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
    Func *output = add_create(MIDI_NOTE_COUNT, array);
    free_(array);
    return output;
}

#endif // CSYNTH_MIDIS_H
