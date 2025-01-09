#ifndef CSYNTH_STEP_H
#define CSYNTH_STEP_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double step_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    double edge = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    double value = input < edge ? 0.0 : 1.0;
    return value;
}

/**
 * @brief Create a function for the step function that outputs a binary
 * threshold.
 *
 * This function creates a generator that implements a simple threshold or step
 * function. It compares an input value against an edge threshold and outputs
 * either 0 or 1 based on whether the input is less than or greater than/equal
 * to the edge.
 *
 * The step function behavior is:
 * - Output is 0 when input < edge
 * - Output is 1 when input >= edge
 * - Discontinuous transition at edge point
 *
 * Common applications include:
 * - Binary thresholding of signals
 * - Creating gate signals from continuous inputs
 * - Basic waveform generation (square waves)
 * - Digital logic operations
 *
 * For a smooth transition between values, consider using smooth_create()
 * instead which provides continuous interpolation between edges.
 *
 * @param edge Function that defines the threshold value. When input crosses
 *             this value, output switches between 0 and 1.
 * @param input Function whose output will be compared against the edge to
 *              determine the binary output state.
 * @return Func* Step function that outputs either 0 or 1.
 */
Func *step_create(Func *edge, Func *input)
{
    return func_create(NULL, step_eval, NULL, NULL, 0, NULL, FuncFlagNone, edge, input);
}

#endif // CSYNTH_STEP_H
