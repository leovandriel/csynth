//
// keyboard.h - Misc keyboard controls
//
#ifndef CSYNTH_KEYBOARD_H
#define CSYNTH_KEYBOARD_H

#include <math.h>

#include "../../core/func.h"
#include "../../util/error.h"
#include "../op/add.h"
#include "../time/times.h"

typedef Func *(*keyboard_control_func)(int key, Func *input);

const char *KEYBOARD_KEYS = "zsxdcvgbhnjm,l.;/"; // assumes US keyboard layout

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
        Func *pitched = pitch_(exp2((double)i / (double)semitones), input);
        array[i] = control(key, pitched);
    }
    Func *output = add_create(count, array);
    free_(array);
    return output;
}

#endif // CSYNTH_KEYBOARD_H
