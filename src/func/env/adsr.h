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

#include <assert.h>
#include <math.h>

#include "../../core/func.h"
#include "../gen/const.h"

typedef struct
{
    double time;
} AdsrContext;

double adsr_eval(Gen **args, __attribute__((unused)) int count, double delta, void *_context)
{
    AdsrContext *context = (AdsrContext *)_context;
    double attack = gen_eval(args[0]);
    double decay = gen_eval(args[1]);
    double sustain = gen_eval(args[2]);
    double release = gen_eval(args[3]);
    double duration = gen_eval(args[4]);
    double output = 0.0;
    if (context->time < attack)
    {
        output = context->time / attack;
    }
    else if (context->time < attack + decay)
    {
        output = 1.0 - (context->time - attack) * (1.0 - sustain) / decay;
    }
    else if (context->time < duration - release)
    {
        output = sustain;
    }
    else if (context->time < duration)
    {
        output = (duration - context->time) * sustain / release;
    }
    context->time += delta;
    return output;
}

Func *adsr(Func *attack, Func *decay, Func *sustain, Func *release, Func *duration)
{
    return func_create(NULL, adsr_eval, NULL, sizeof(AdsrContext), NULL, 5, attack, decay, sustain, release, duration);
}

#define adsr_(_attack, _decay, _sustain, _release, _duration) (adsr(const_(_attack), const_(_decay), const_(_sustain), const_(_release), const_(_duration)))

void test_adsr()
{
    func t = adsr_(0.01, 0.1, 0.7, 0.2, 1.2);
    Gen *g = gen_create(t, 0.1);
    double epsilon = 1e-9;
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.730000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.700000) < epsilon);
    assert(fabs(gen_eval(g) - 0.350000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
    assert(fabs(gen_eval(g) - 0.000000) < epsilon);
}

#endif // CSYNTH_ADSR_H
