#ifndef CSYNTH_OVERTONE_H
#define CSYNTH_OVERTONE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"
#include "../op/add.h"
#include "../op/mul.h"
#include "../op/pow.h"
#include "../util/scale.h"

/**
 * @brief Create a function that generates overtones.
 *
 * @param range Number of octaves to generate overtones.
 * @param gain Gain of each overtone.
 * @param input Input function.
 * @return Func* Overtone function.
 */
Func *overtone_create(int range, Func *gain, Func *input)
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
        double gain_factor = (double)i / (double)(count - 1);
        double pitch_factor = exp2((double)i * sign);
        Func *gain_ = pow_create(const_(M_E), mul_create(ARGS(const_(gain_factor), gain)));
        Func *input_ = scale_create(EvalParamPitchTick, const_(pitch_factor), input);
        array[i] = mul_create(ARGS(gain_, input_));
    }
    Func *output = add_create(count, array);
    free_(array);
    return output;
}

#endif // CSYNTH_OVERTONE_H
