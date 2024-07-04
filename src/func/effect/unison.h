//
// unison.h - A unison generator
//
// `unison(frequency, generator, count, detune)`
//
#ifndef CSYNTH_UNISON_H
#define CSYNTH_UNISON_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/gens.h"
#include "../op/ops.h"

Func *unison_split(size_t count, Func *input)
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
    Func *output = avg_create(count, array);
    free_(array);
    return output;
}

Func *unison(size_t count, Func *detune, Func *input) /* unison_ */
{
    return unison_split(count, pitch(add_(1, mul(detune, sample())), input));
}
Func *unison_(size_t count, double detune, Func *input) { return unison(count, const_(detune), input); }

#endif // CSYNTH_UNISON_H
