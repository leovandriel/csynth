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

Func *overtone(int range, Func *gain, Func *input)
{
    int count = abs(range);
    Func **array = (Func **)malloc_(count * sizeof(Func *));
    if (array == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    int sign = range < 0 ? -1 : 1;
    for (int i = 0; i < count; i++)
    {
        Func *_gain = gauge("abc", expo2(mul_((double)i / count, gain)));
        array[i] = mul(_gain, pitch_(exp2(i * sign), input));
    }
    Func *output = dvd_(add_create(count, array), count);
    free_(array);
    return output;
}

Func *overtone_(int count, double gain, Func *input) { return overtone(count, const_(gain), input); }

#endif // CSYNTH_OVERTONE_H
