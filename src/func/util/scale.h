#ifndef CSYNTH_SCALE_H
#define CSYNTH_SCALE_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"
#include "../op/inv.h"
#include "../op/mul.h"
#include "../op/pow.h"

/** @see scale_create */
typedef struct
{
    /** @brief Eval param to scale. */
    EvalParam param;
} ScaleContext;

static double scale_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    ScaleContext *context = (ScaleContext *)context_;
    double factor = gen_eval(args[0], eval);
    if (eval == NULL)
    {
        return gen_eval(args[1], eval);
    }
    double restore = eval->params[context->param];
    eval->params[context->param] = restore * factor;
    double input = gen_eval(args[1], eval);
    eval->params[context->param] = restore;
    return input;
}

/**
 * @brief Create a function that scales an eval param by a factor.
 *
 * This can be used to scale the frequency (pitch) of a generator, for example.
 *
 * @param param Eval param to scale.
 * @param factor Factor to multiply by.
 * @param input Input signal, which is returned unchanged.
 * @return Func* Scale function.
 */
Func *scale_create(EvalParam param, Func *factor, Func *input)
{
    ScaleContext initial = {.param = param};
    return func_create(NULL, scale_eval, NULL, NULL, sizeof(ScaleContext), &initial, FuncFlagNone, factor, input);
}

/** @brief Shorthand for `scale_create`. */
Func *scale(EvalParam param, Func *factor, Func *input) { return scale_create(param, factor, input); }

Func *pitch_shift(Func *octaves, Func *input) { return scale_create(EvalParamPitchTick, pow_create(const_(2.0), octaves), input); }
Func *pitch_shift_ratio(Func *shift, Func *semitones, Func *input) { return pitch_shift(mul_create(ARGS_FUNC(shift, inv_create(semitones))), input); }
Func *pitch_shift_(double octaves, Func *input) { return scale_create(EvalParamPitchTick, const_(exp2(octaves)), input); }

#endif // CSYNTH_SCALE_H
