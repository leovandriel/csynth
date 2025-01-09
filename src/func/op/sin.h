#ifndef CSYNTH_SIN_H
#define CSYNTH_SIN_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see sin_create */
typedef struct
{
    /** @brief Cached output value. */
    double output;
} SinContext;

static double sin_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    SinContext *context = (SinContext *)context_;
    double angle = gen_eval(args[0], eval);
    if (eval == NULL || eval->compute_flag)
    {
        context->output = sin(angle);
    }
    return context->output;
}

/**
 * @brief Create a function for the sine function, i.e. sin(angle).
 *
 * This function creates a generator that computes the sine of its input angle.
 * Due to the computational cost of the sin() function, the result is cached in
 * the context and only recomputed when the compute_flag is set in the
 * evaluator. This is intended for signal processing operations that need sine
 * calculations, not for generating continuous sine waves (use oscillator
 * functions instead).
 *
 * Common applications include:
 * - Phase calculations in signal processing
 * - Circular/trigonometric transformations
 * - Modulation effects using sine-based waveshaping
 * - Mathematical operations requiring sine
 *
 * The output range will always be [-1, 1] regardless of input:
 * - Input angle in radians (2π = one full cycle)
 * - Output is symmetric around 0
 * - Peaks at +1 when angle = π/2 + 2πn
 * - Troughs at -1 when angle = 3π/2 + 2πn
 *
 * @param angle Function whose output provides the angle in radians. The sine
 *             will be computed for each angle value.
 * @return Func* Sine function.
 */
Func *sin_create(Func *angle)
{
    return func_create(NULL, sin_eval, NULL, NULL, sizeof(SinContext), NULL, FuncFlagNone, angle);
}

#endif // CSYNTH_SIN_H
