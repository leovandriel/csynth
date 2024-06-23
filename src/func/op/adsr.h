//
// adsr.h - ADSR envelope
//
// `adsr(attack, decay, sustain, release, duration)` with:
// - `attack` - Attack time
// - `decay` - Decay time
// - `sustain` - Sustain level [0, 1]
// - `release` - Release time
// - `duration` - The full duration of the envelope (attach + decay + sustain +
//   release)
//
#ifndef CSYNTH_ADSR_H
#define CSYNTH_ADSR_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/const.h"

static double adsr_eval(__U int count, Gen **args, __U double delta, __U void *context_)
{
    double time = gen_eval(args[0]);
    double attack = gen_eval(args[1]);
    double decay = gen_eval(args[2]);
    double sustain = gen_eval(args[3]);
    double release = gen_eval(args[4]);
    double duration = gen_eval(args[5]);
    double output = 0.0;
    if (time < attack)
    {
        output = time / attack;
    }
    else if (time < attack + decay)
    {
        output = 1.0 - (time - attack) * (1.0 - sustain) / decay;
    }
    else if (time < duration - release)
    {
        output = sustain;
    }
    else if (time < duration)
    {
        output = (duration - time) * sustain / release;
    }
    return output;
}

Func *adsr_op(Func *time, Func *attack, Func *decay, Func *sustain, Func *release, Func *duration)
{
    return func_create(NULL, adsr_eval, NULL, 0, NULL, FUNC_FLAG_DEFAULT, 6, time, attack, decay, sustain, release, duration);
}
Func *adsr_op_(Func *time, double attack, double decay, double sustain, double release, double duration) { return adsr_op(time, const_(attack), const_(decay), const_(sustain), const_(release), const_(duration)); }

#endif // CSYNTH_ADSR_H
