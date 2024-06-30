//
// keyboards.h - Misc keyboard controls
//
#ifndef CSYNTH_KEYBOARDS_H
#define CSYNTH_KEYBOARDS_H

#include <math.h>

#include "../../core/func.h"
#include "../../util/error.h"
#include "../gen/gens.h"
#include "../gen/notes.h"
#include "../op/add.h"
#include "../op/mul.h"
#include "../time/times.h"
#include "./replay.h"

typedef Func *(*keyboard_control_func)(int key, Func *input);

const char *keyboard_keys = "zsxdcvgbhnjm,l.;/";

Func *keyboard(keyboard_control_func control, Func *input)
{
    int count = (int)strlen(keyboard_keys);
    Func **array = (Func **)malloc_(count * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    for (int i = 0; i < count; i++)
    {
        char key = keyboard_keys[i];
        Func *pitched = pitch_(exp2(i / 12.0), input);
        array[i] = control(key, pitched);
    }
    Func *output = add_array(count, array);
    free_(array);
    return output;
}

Func *replay(const char *filename, Func *input) { return replay_tick(filename, tempo_ticker_(1), input); }
Func *replay_(Func *input) { return replay(DEFAULT_REC_FILENAME, input); }

#endif // CSYNTH_KEYBOARDS_H
