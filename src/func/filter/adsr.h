#ifndef CSYNTH_ADSR_H
#define CSYNTH_ADSR_H

#include "../../core/func.h"
#include "../../core/gen.h"

static double adsr_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    // TODO(leo): remove time and sustain, use tick instead
    double time = gen_eval(args[0], eval);
    double attack = gen_eval(args[1], eval);
    double decay = gen_eval(args[2], eval);
    double sustain = gen_eval(args[3], eval);
    double release = gen_eval(args[4], eval);
    double duration = gen_eval(args[5], eval);
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

/**
 * @brief Create a function that generates ADSR envelope.
 *
 * @param time The time offset at which to evaluate the envelope.
 * @param attack The attack time.
 * @param decay The decay time.
 * @param sustain The sustain level, between 0 and 1.
 * @param release The release time.
 * @param duration The full duration of the envelope.
 * @return Func* ADSR function.
 */
Func *adsr_create(Func *time, Func *attack, Func *decay, Func *sustain, Func *release, Func *duration)
{
    return func_create(NULL, adsr_eval, NULL, 0, NULL, FuncFlagNone, time, attack, decay, sustain, release, duration);
}

#endif // CSYNTH_ADSR_H
