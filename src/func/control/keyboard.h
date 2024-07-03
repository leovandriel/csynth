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

const char *KEYBOARD_KEYS = "zsxdcvgbhnjm,l.;/";

Func *keyboard(keyboard_control_func control, Func *input)
{
    int count = (int)strlen(KEYBOARD_KEYS);
    Func **array = (Func **)malloc_(count * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    for (int i = 0; i < count; i++)
    {
        char key = KEYBOARD_KEYS[i];
        Func *pitched = pitch_(exp2(i / 12.0), input);
        array[i] = control(key, pitched);
    }
    Func *output = add_create(count, array);
    free_(array);
    return output;
}

#endif // CSYNTH_KEYBOARD_H
