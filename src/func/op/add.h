#ifndef CSYNTH_ADD_H
#define CSYNTH_ADD_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double add_eval(size_t count, Gen **args, Eval *eval, __U void *context)
{
    double sum = 0;
    for (size_t i = 0; i < count; i++)
    {
        sum += gen_eval(args[i], eval);
    }
    return sum;
}

/**
 * @brief Create a function that sums across all inputs.
 *
 * This function creates a generator that adds together the output values from
 * multiple input functions. Each input function is evaluated and their outputs
 * are summed together to produce the final result. This is commonly used for
 * mixing multiple audio signals together, such as combining different
 * instruments or sound effects into a final mix.
 *
 * The output range will be the sum of the input ranges. For example, if mixing
 * two signals that each output in [-1, 1], the output could range from -2 to
 * +2. Consider scaling the output if a specific range is needed.
 *
 * @param count Number of input functions to sum together.
 * @param args Array of input functions to be summed. Must contain count
 *            elements. Each function will be evaluated once per sample.
 * @return Func* Addition function that outputs the sum of all inputs.
 */
Func *add_create(size_t count, Func **args)
{
    return func_create_args(NULL, add_eval, NULL, NULL, 0, NULL, FuncFlagNone, count, args, "arg");
}

#endif // CSYNTH_ADD_H
