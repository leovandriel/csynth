#ifndef CSYNTH_PATTERN_H
#define CSYNTH_PATTERN_H

#include <stdlib.h>

#include "../../core/func.h"
#include "../../util/random.h"
#include "../gen/gens.h"
#include "../op/ops.h"
#include "./seq.h"

/**
 * @brief A trigger pattern defined in a string.
 *
 * @param string String of '.' and ' ' characters.
 * @param duration Duration of each character.
 * @param timing Timing variance of each trigger.
 * @param input Input function to be triggered.
 * @return Func* Pattern function.
 */
Func *pattern_create(const char *string, Func *duration, Func *timing, Func *input)
{
    Random random = random_create(0);
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
            array[index++] = add(mul_(i, duration), mul_(random_gauss(&random, 0, 1), timing));
            array[index++] = input;
        }
    }
    Func *output = seq_abs_create(index, array);
    free_(array);
    return output;
}

#endif // CSYNTH_PATTERN_H
