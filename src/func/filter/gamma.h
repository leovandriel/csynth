#ifndef CSYNTH_GAMMA_H
#define CSYNTH_GAMMA_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../util/math.h"

typedef double (*gamma_mapping)(double amplitude, double param);

double map_gamma(double amplitude, double exponent) // gamma_mapping
{
    if (exponent < 0)
    {
        return math_pow_int(amplitude, -(int)exponent);
    }
    return math_gamma(amplitude, (int)exponent);
}

double map_circle(double amplitude, double shape) // gamma_mapping
{
    if (shape < 0)
    {
        return 1 - math_sqrt_0to1(1 - amplitude * amplitude);
    }
    return math_sqrt_0to1(amplitude * (2 - amplitude));
}

/** @brief See gamma_create */
typedef struct
{
    /** @brief Function mapping [0, 1] to [0, 1] */
    gamma_mapping mapping;
} GammaContext;

static double gamma_eval(__U size_t count, Gen **args, Eval *eval, __U void *_context)
{
    GammaContext *context = (GammaContext *)_context;
    double input = gen_eval(args[0], eval);
    double param = gen_eval(args[1], eval);
    double amplitude = fabs(input);
    double sign = (input > 0) - (input < 0);
    return context->mapping(amplitude, param) * sign;
}

/**
 * @brief Create a function that map triangle wave shape with arbitrary function.
 *
 * @param input Function whose output will be mapped. Each sample will be
 *             mapped individually.
 * @param param Function whose output is passed into mapping as param.
 * @return Func* Gamma function.
 */
Func *gamma_create(Func *input, Func *param, gamma_mapping mapping)
{
    GammaContext initial = {.mapping = mapping};
    return func_create(NULL, gamma_eval, NULL, NULL, sizeof(GammaContext), &initial, FuncFlagNone, input, param);
}

#endif // CSYNTH_GAMMA_H
