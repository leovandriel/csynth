//
// pitch.h - Pitch shift
//
#ifndef CSYNTH_PITCH_H
#define CSYNTH_PITCH_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double pitch_eval(__U int count, Gen **args, Eval eval, __U void *context_)
{
    eval.audio_step *= gen_eval(args[1], eval);
    return gen_eval(args[0], eval);
}

Func *pitch(Func *input, Func *factor)
{
    return func_create(NULL, pitch_eval, NULL, 0, NULL, FuncFlagNone, 2, input, factor);
}

Func *pitch_(Func *input, double factor) { return pitch(input, const_(factor)); }

#endif // CSYNTH_PITCH_H
