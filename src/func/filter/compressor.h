#ifndef CSYNTH_COMPRESSOR_H
#define CSYNTH_COMPRESSOR_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

/** @see compressor_create */
typedef struct
{
    /** @brief Compressor gain. */
    double gain;
    /** @brief Compressor target gain. */
    double target;
    /** @brief Compressor coefficient. */
    double coeff;
} CompressorContext;

static double compressor_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    CompressorContext *context = (CompressorContext *)context_;
    double threshold = gen_eval(args[0], eval);
    double ratio = gen_eval(args[1], eval);
    double attack_tick = gen_eval(args[2], eval);
    double release_tick = gen_eval(args[3], eval);
    double input = gen_eval(args[4], eval);
    if (eval == NULL || eval->compute_flag)
    {
        double level = fabs(input);
        context->target = level > threshold ? pow(threshold / level, ratio) : 1.0;
        context->coeff = -expm1(context->target < context->gain ? -attack_tick : -release_tick);
    }
    context->gain += (context->target - context->gain) * context->coeff;
    return input * context->gain;
}

/**
 * @brief Create a function that implements a compressor effect.
 *
 * @param threshold Level at which the compressor starts to reduce gain [0..1].
 * @param ratio Compression ratio [0..1].
 * @param attack_tick Attack in seconds.
 * @param release_tick Release in seconds.
 * @param input Input signal.
 * @return Func* Compressor function.
 */
Func *compressor_create(Func *threshold, Func *ratio, Func *attack_tick, Func *release_tick, Func *input)
{
    CompressorContext initial = {.gain = 1.0};
    return func_create(NULL, compressor_eval, NULL, sizeof(CompressorContext), &initial, FuncFlagNone, threshold, ratio, attack_tick, release_tick, input);
}

#endif // CSYNTH_COMPRESSOR_H
