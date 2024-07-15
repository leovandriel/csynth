//
// pattern.h - Pattern
//
#ifndef CSYNTH_PATTERN_H
#define CSYNTH_PATTERN_H

#include <stdlib.h>

#include "../../core/func.h"
#include "../../util/rand.h"
#include "../gen/gens.h"
#include "../op/ops.h"
#include "./seq.h"

Func *pattern_create(const char *string, Func *duration, Func *timing, Func *input)
{
    size_t length = strlen(string);
    Func **array = (Func **)malloc_(length * 2 * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    size_t index = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (string[i] == '.')
        {
            array[index++] = add(mul_(i, duration), mul_(rand_gauss(0, 1), timing));
            array[index++] = input;
        }
    }
    Func *output = seq_abs_create(index, array);
    free_(array);
    return output;
}

#endif // CSYNTH_PATTERN_H
