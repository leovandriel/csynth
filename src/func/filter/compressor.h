//
// compressor.h - Compression effect
//
// `compressor(input, threshold, ratio, attack, release)`
// - `input` - Input signal
// - `threshold` - Level at which the compressor starts to reduce gain [0..1]
// - `ratio` - Compression ratio [0..1]
// - `attack` - Attack in seconds
// - `release` - Release in seconds
//
#ifndef CSYNTH_COMPRESSOR_H
#define CSYNTH_COMPRESSOR_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"

typedef struct
{
    double gain;
} CompressorContext;

static double compressor_eval(__U int count, Gen **args, Eval eval, void *context_)
{
    CompressorContext *context = (CompressorContext *)context_;
    double threshold = gen_eval(args[0], eval);
    double ratio = gen_eval(args[1], eval);
    double attack_tick = gen_eval(args[2], eval);
    double release_tick = gen_eval(args[3], eval);
    double input = gen_eval(args[4], eval);
    double level = fabs(input);
    double target = level > threshold ? pow(threshold / level, ratio) : 1.0;
    double coeff = -expm1(target < context->gain ? -attack_tick : -release_tick);
    context->gain += (target - context->gain) * coeff;
    return input * context->gain;
}

Func *compressor_create(Func *threshold, Func *ratio, Func *attack_tick, Func *release_tick, Func *input)
{
    CompressorContext initial = {.gain = 1.0};
    return func_create(NULL, compressor_eval, NULL, sizeof(CompressorContext), &initial, FuncFlagNone, FUNCS(threshold, ratio, attack_tick, release_tick, input));
}

#endif // CSYNTH_COMPRESSOR_H
