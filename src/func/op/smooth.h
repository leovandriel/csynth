#ifndef CSYNTH_SMOOTH_H
#define CSYNTH_SMOOTH_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double smooth_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    double edge0 = gen_eval(args[0], eval);
    double edge1 = gen_eval(args[1], eval);
    double input = gen_eval(args[2], eval);
    if ((edge0 <= edge1 && input < edge0) || (edge0 > edge1 && input >= edge0))
    {
        return 0.0;
    }
    if ((edge0 >= edge1 && input <= edge1) || (edge0 <= edge1 && input >= edge1))
    {
        return 1.0;
    }
    double ratio = (input - edge0) / (edge1 - edge0);
    return ratio * ratio * (3.0 - 2.0 * ratio);
}

/**
 * @brief Create a function for the smooth step function that performs Hermite
 * interpolation between edges.
 *
 * This function creates a generator that smoothly transitions between 0 and 1
 * using a cubic Hermite polynomial interpolation (smoothstep). The transition
 * occurs between two edge values, with a continuous first derivative at the
 * edges for smooth transitions.
 *
 * The interpolation follows the formula: t * t * (3 - 2t) where t is the
 * normalized position between edge0 and edge1. This creates an S-shaped curve
 * with the following properties:
 * - Output is 0 when input <= edge0
 * - Output is 1 when input >= edge1
 * - Smooth transition between edges with zero derivatives at edges
 * - Monotonically increasing between edges
 *
 * If edge0 > edge1, the function behavior is reversed:
 * - Output is 1 when input <= edge1
 * - Output is 0 when input >= edge0
 * - Smooth transition occurs from 1 to 0 between edges
 *
 * Common applications include:
 * - Crossfading between signals
 * - Creating envelope shapes
 * - Smooth parameter automation
 * - Anti-aliased thresholding
 *
 * @param edge0 Function that defines the first transition edge. When input is
 *              below this value (or above for reversed case), output will be 0.
 * @param edge1 Function that defines the second transition edge. When input is
 *              above this value (or below for reversed case), output will be 1.
 * @param input Function whose output will be compared against the edges to
 *              determine the interpolation position.
 * @return Func* Smooth step function that outputs values in range [0,1].
 */
Func *smooth_create(Func *edge0, Func *edge1, Func *input)
{
    return func_create(NULL, smooth_eval, NULL, NULL, 0, NULL, FuncFlagNone, edge0, edge1, input);
}

#endif // CSYNTH_SMOOTH_H
