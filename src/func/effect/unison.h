#ifndef CSYNTH_UNISON_H
#define CSYNTH_UNISON_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"
#include "../op/add.h"
#include "../op/mul.h"

/**
 * @brief Create a function that generates unison by averaging copies of input
 * function.
 *
 * This is usually combined with detune to create a unison effect.
 *
 * @param count Number of signals.
 * @param input Input signal to be duplicated.
 * @return Func* Unison function.
 */
Func *unison_create(size_t count, Func *input)
{
    Func **array = (Func **)malloc_(count * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    for (size_t i = 0; i < count; i++)
    {
        array[i] = input;
    }
    Func *output = mul_create(ARGS(add_create(count, array), const_(1.0 / count)));
    free_(array);
    return output;
}

#endif // CSYNTH_UNISON_H
