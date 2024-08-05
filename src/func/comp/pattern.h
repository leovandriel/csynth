#ifndef CSYNTH_PATTERN_H
#define CSYNTH_PATTERN_H

#include <stdlib.h>

#include "../../core/func.h"
#include "../../util/random.h"
#include "../gen/const.h"
#include "../gen/sample.h"
#include "../op/add.h"
#include "../op/mul.h"
#include "./seq.h"

/**
 * @brief A trigger pattern defined in a string.
 *
 * @param string String of '.' and ' ' characters.
 * @param tick Periods per sample.
 * @param timing Timing variance of each trigger.
 * @param input Input function to be triggered.
 * @return Func* Pattern function.
 */
Func *pattern_create(const char *string, Func *tick, Func *timing, Func *input)
{
    size_t length = strlen(string);
    Func **array = (Func **)malloc_((length * 2 + 1) * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    size_t index = 0;
    array[index++] = tick;
    for (size_t i = 0; i < length; i++)
    {
        if (string[i] == '.')
        {
            array[index++] = add_create(ARGS(const_create(i), mul_create(ARGS(sample_gauss_create(), timing))));
            array[index++] = input;
        }
    }
    Func *output = seq_abs_create(index, array);
    free_(array);
    return output;
}

#endif // CSYNTH_PATTERN_H
