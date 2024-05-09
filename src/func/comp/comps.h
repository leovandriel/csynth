//
// comps.h - Compositions
//
#ifndef CSYNTH_COMPS_H
#define CSYNTH_COMPS_H

#include <stdlib.h>

#include "../../core/func.h"
#include "../gen/gens.h"
#include "../op/mul.h"
#include "../op/add.h"
#include "../../util/rand.h"
#include "./seq.h"

Func *pattern(const char *string, Func *f, Func *duration, Func *timing)
{
    int length = strlen(string);
    Func **array = (Func **)calloc(length * 2, sizeof(Func *));
    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if (string[i] == '.')
        {
            array[index++] = add(mul_(duration, i), mul_(timing, rand_gauss(0, 1)));
            array[index++] = f;
        }
    }
    Func *func = seq_abs_array(index, array);
    free(array);
    return func;
}

Func *pattern_(const char *string, Func *f, double duration, double timing)
{
    return pattern(string, f, const_(duration), const_(timing));
}

#endif // CSYNTH_COMPS_H
