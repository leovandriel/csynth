//
// overtone.h - A overtone generator
//
#ifndef CSYNTH_OVERTONE_H
#define CSYNTH_OVERTONE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"
#include "../gen/gens.h"
#include "../op/ops.h"
#include "../util/utils.h"

Func *overtone(int range, Func *gain, Func *input) /* overtone_ */
{
    size_t count = abs(range);
    Func **array = (Func **)malloc_(count * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    double sign = range < 0 ? -1.0 : 1.0;
    for (size_t i = 0; i < count; i++)
    {
        Func *_gain = expo2(mul_((double)i / (double)(count - 1), gain));
        array[i] = mul(_gain, pitch_(exp2((double)i * sign), input));
    }
    Func *output = add_create(count, array);
    free_(array);
    return output;
}

Func *overtone_(int range, double gain, Func *input) { return overtone(range, const_(gain), input); }

#endif // CSYNTH_OVERTONE_H
