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
#include "../op/add.h"
#include "../op/mul.h"
#include "../op/ops.h"
#include "./gens.h"

Func *unison(Func *frequency, gen_func generator, int count, double detune)
{
    Func **array = (Func **)calloc_(count, sizeof(Func *));
    for (int i = 0; i < count; i++)
    {
        array[i] = generator(mul_(frequency, rand_range(1 - detune, 1 + detune)));
    }
    Func *func = dvd_(add_array(count, array), count);
    free_(array);
    return func;
}

#endif // CSYNTH_UNISON_H
