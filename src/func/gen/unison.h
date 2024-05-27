//
// unison.h - A unison generator
//
// `unison(frequency, generator, count, detune)`
//
#ifndef CSYNTH_UNISON_H
#define CSYNTH_UNISON_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "./gens.h"
#include "../../util/rand.h"
#include "../op/mul.h"
#include "../op/add.h"

Func *unison(Func *frequency, gen_func generator, int count, double detune)
{
    Func **array = (Func **)calloc(count, sizeof(Func *));
    for (int i = 0; i < count; i++)
    {
        array[i] = generator(mul_(frequency, rand_range(1 - detune, 1 + detune)));
    }
    Func *func = add_array(count, array);
    free(array);
    return func;
}

#endif // CSYNTH_UNISON_H
