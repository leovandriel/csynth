//
// comps.h - Compositions
//
#ifndef CSYNTH_COMPS_H
#define CSYNTH_COMPS_H

#include <stdlib.h>

#include "../../core/func.h"
#include "../../util/rand.h"
#include "../gen/gens.h"
#include "../op/add.h"
#include "../op/mul.h"
#include "./seq.h"

Func *pattern(const char *string, Func *input, Func *duration, Func *timing)
{
    int length = (int)strlen(string);
    Func **array = (Func **)malloc_(length * 2 * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if (string[i] == '.')
        {
            array[index++] = add(mul_(duration, i), mul_(timing, rand_gauss(0, 1)));
            array[index++] = input;
        }
    }
    Func *func = seq_abs_array(index, array);
    free_(array);
    return func;
}

Func *pattern_(const char *string, Func *input, double duration, double timing)
{
    return pattern(string, input, const_(duration), const_(timing));
}

#endif // CSYNTH_COMPS_H
