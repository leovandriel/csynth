#ifndef CSYNTH_MUL_H
#define CSYNTH_MUL_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double mul_eval(size_t count, Gen **args, Eval *eval, __U void *context)
{
    double output = 1.0;
    for (size_t i = 0; i < count; i++)
    {
        output *= gen_eval(args[i], eval);
    }
    return output;
}

/**
 * @brief Create a function that multiplies together all inputs.
 *
 * This function creates a generator that multiplies together the output values
 * from multiple input functions. Each input function is evaluated and their
 * outputs are multiplied together to produce the final result. This is commonly
 * used for applying gain/amplitude modulation to audio signals, such as
 * controlling the volume of a sound or creating tremolo effects.
 *
 * Common applications include:
 * - Scaling a signal by multiplying with a constant gain factor
 * - Amplitude modulation by multiplying with an oscillator or envelope
 * - Ring modulation between two audio signals
 * - Creating complex modulation chains
 *
 * The output range will be the product of the input ranges. For example, when
 * multiplying a [-1, 1] audio signal by a [0, 1] envelope, the output will be
 * in [-1, 1]. Be careful when multiplying multiple full-range signals as the
 * output can grow exponentially.
 *
 * @param count Number of input functions to multiply together. Must be greater
 * than 0.
 * @param args Array of input functions to be multiplied. Must contain count
 *            elements. Each function will be evaluated once per sample.
 * @return Func* Multiplication function that outputs the product of all inputs.
 */
Func *mul_create(size_t count, Func **args)
{
    return func_create_args(NULL, mul_eval, NULL, NULL, 0, NULL, FuncFlagNone, count, args, "arg");
}

#endif // CSYNTH_MUL_H
