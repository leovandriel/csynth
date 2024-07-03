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

Func *pattern(const char *string, Func *duration, Func *timing, Func *input) /* pattern_ */
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
            array[index++] = add(mul_(i, duration), mul_(rand_gauss(0, 1), timing));
            array[index++] = input;
        }
    }
    Func *output = seq_abs_create(index, array);
    free_(array);
    return output;
}

Func *pattern_(const char *string, double duration, double timing, Func *input)
{
    return pattern(string, const_(duration), const_(timing), input);
}

#endif // CSYNTH_PATTERN_H
