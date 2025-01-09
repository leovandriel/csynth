#ifndef CSYNTH_MIN_H
#define CSYNTH_MIN_H

#include <float.h>

#include "../../core/func.h"
#include "../../core/gen.h"

static double min_eval(size_t count, Gen **args, Eval *eval, __U void *context)
{
    double min = FLT_MAX;
    for (size_t i = 0; i < count; i++)
    {
        double input = gen_eval(args[i], eval);
        if (min > input)
        {
            min = input;
        }
    }
    return min;
}

/**
 * @brief Create a function that outputs the minimum value across all inputs.
 *
 * This function creates a generator that evaluates multiple input functions and
 * outputs the smallest value among them for each sample. It compares the
 * outputs of all input functions and returns the minimum value found. This is
 * useful for implementing various audio effects and signal processing
 * operations.
 *
 * Common applications include:
 * - Clamping a signal to a minimum value by comparing it with a constant
 * - Creating waveshaping/distortion effects by combining with other functions
 * - Implementing minimum-based envelope followers
 * - Building more complex signal processing chains
 *
 * The output range will be bounded by the minimum possible output of any input
 * function. For normalized audio signals in [-1, 1], the output will also stay
 * within that range.
 *
 * @param count Number of input functions to compare. Must be greater than 0.
 * @param args Array of input functions to find minimum across. Must contain
 *            count elements. Each function will be evaluated once per sample.
 * @return Func* Minimum function that outputs the smallest value across all
 *         inputs for each sample.
 */
Func *min_create(size_t count, Func **args)
{
    return func_create_args(NULL, min_eval, NULL, NULL, 0, NULL, FuncFlagNone, count, args, "arg");
}

#endif // CSYNTH_MIN_H
