#ifndef CSYNTH_KEYBOARD_H
#define CSYNTH_KEYBOARD_H

#include <math.h>

#include "../../core/func.h"
#include "../../util/error.h"
#include "../gen/const.h"
#include "../op/add.h"
#include "../util/scale.h"

typedef Func *(*keyboard_control_func)(int key, Func *input);

const char *KEYBOARD_KEYS = "zsxdcvgbhnjm,l.;/"; // assumes US keyboard layout

/**
 * @brief A keyboard control function that maps a key stroke to a pitch of a
 * single function.
 *
 * @param semitones Number of semitones in an octave.
 * @param control Function that maps a key to a pitch of a single function.
 * @param input Input function to pitch and trigger.
 * @return Func* Keyboard function.
 */
Func *keyboard_create(size_t semitones, keyboard_control_func control, Func *input)
{
    size_t count = strlen(KEYBOARD_KEYS);
    Func **array = (Func **)malloc_(count * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    for (size_t i = 0; i < count; i++)
    {
        char key = KEYBOARD_KEYS[i];
        double pitch_factor = exp2((double)i / (double)semitones);
        Func *pitched = scale_create(EvalParamPitchTick, const_(pitch_factor), input);
        array[i] = control(key, pitched);
    }
    Func *output = add_create(count, array);
    free_(array);
    return output;
}

#endif // CSYNTH_KEYBOARD_H
