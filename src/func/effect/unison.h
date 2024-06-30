//
// unison.h - A unison generator
//
// `unison(frequency, generator, count, detune)`
//
#ifndef CSYNTH_UNISON_H
#define CSYNTH_UNISON_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/rand.h"
#include "../gen/gens.h"
#include "../gen/sample.h"
#include "../op/add.h"
#include "../op/mul.h"
#include "../op/ops.h"

Func *unison_split(int count, Func *input)
{
    Func **array = (Func **)malloc_(count * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    for (int i = 0; i < count; i++)
    {
        array[i] = input;
    }
    Func *output = dvd_(add_array(count, array), count);
    free_(array);
    return output;
}

Func *unison(int count, Func *detune, Func *input)
{
    return unison_split(count, pitch(add_(1, mul(detune, sample())), input));
}
Func *unison_(int count, double detune, Func *input) { return unison(count, const_(detune), input); }

#endif // CSYNTH_UNISON_H
