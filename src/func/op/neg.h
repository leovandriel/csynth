#ifndef CSYNTH_NEG_H
#define CSYNTH_NEG_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double neg_eval(__U size_t count, Gen **args, Eval *eval, __U void *context)
{
    double input = gen_eval(args[0], eval);
    return -input;
}

/**
 * @brief Create a function that negates the input, i.e. -input.
 *
 * This function creates a generator that outputs the negative of its input
 * value. For any input x, it outputs -x. This is useful for inverting signals
 * or creating phase-inverted copies of audio waveforms.
 *
 * Common applications include:
 * - Phase inversion of audio signals
 * - Creating bipolar signals from unipolar ones
 * - Implementing subtraction using addition (a - b = a + (-b))
 * - Building more complex signal processing chains
 *
 * The output range will be the negation of the input range. For example:
 * - Input range [0, 1] -> Output range [-1, 0]
 * - Input range [-1, 1] -> Output range [-1, 1]
 * - Input range [-0.5, 0.5] -> Output range [-0.5, 0.5]
 *
 * @param input Function whose output will be negated. Each sample will be
 *             negated individually.
 * @return Func* Negation function that outputs -input for each input value.
 */
Func *neg_create(Func *input)
{
    return func_create(NULL, neg_eval, NULL, NULL, 0, NULL, FuncFlagNone, input);
}
#endif // CSYNTH_NEG_H
