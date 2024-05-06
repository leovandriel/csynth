//
// comps.h - Compositions
//
#ifndef CSYNTH_COMPS_H
#define CSYNTH_COMPS_H

#include <stdlib.h>

#include "../../core/func.h"
#include "../gen/const.h"
#include "./comp.h"

Func *pattern(const char *string, Func *f, Func *duration)
{
    int length = strlen(string);
    Func **array = (Func **)calloc(length * 2, sizeof(Func *));
    for (int i = 0; i < length; i++)
    {
        array[i * 2] = string[i] == ' ' ? ZERO : f;
        array[i * 2 + 1] = duration;
    }
    Func *func = comp_rel_array(length * 2, array);
    free(array);
    return func;
}

Func *pattern_(const char *string, Func *f, double duration)
{
    return pattern(string, f, const_(duration));
}

#endif // CSYNTH_COMPS_H
