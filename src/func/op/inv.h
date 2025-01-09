#ifndef CSYNTH_INV_H
#define CSYNTH_INV_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double inv_eval(__U size_t count, Gen **args, Eval *eval, __U void *context)
{
    double input = gen_eval(args[0], eval);
    if (input < FUNC_EPSILON && input > -FUNC_EPSILON)
    {
        input = input >= 0 ? FUNC_EPSILON : -FUNC_EPSILON;
    }
    return 1.0 / input;
}

/**
 * @brief Create a function for the inverse of the input, i.e. 1 / input.
 *
 * This function creates a generator that outputs the reciprocal (multiplicative
 * inverse) of its input value. For any input x, it outputs 1/x. This is useful
 * for creating reciprocal relationships or implementing division through
 * multiplication by the inverse.
 *
 * To prevent division by zero errors, inputs very close to zero (between
 * -FUNC_EPSILON and +FUNC_EPSILON) are clamped to FUNC_EPSILON with the same
 * sign as the input. This provides smooth behavior around zero while avoiding
 * infinite or undefined outputs.
 *
 * The output range depends on the input:
 * - For inputs > FUNC_EPSILON: output is in (0, 1/FUNC_EPSILON)
 * - For inputs < -FUNC_EPSILON: output is in (-1/FUNC_EPSILON, 0)
 * - For inputs near zero: output is ±1/FUNC_EPSILON
 *
 * @param input Function whose reciprocal will be computed. Each sample will be
 *             inverted individually.
 * @return Func* Inverse function that outputs 1/input for each input value.
 */
Func *inv_create(Func *input)
{
    return func_create(NULL, inv_eval, NULL, NULL, 0, NULL, FuncFlagNone, input);
}

#endif // CSYNTH_INV_H
