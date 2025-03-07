#ifndef CSYNTH_EFFECTS_H
#define CSYNTH_EFFECTS_H

#include "../filter/filters.h"
#include "../gen/gens.h"
#include "../util/times.h"
#include "./continuous.h"
#include "./delay.h"
#include "./loop.h"
#include "./overtone.h"
#include "./reverb.h"
#include "./unison.h"

Func *reverb(Func *interval, Func *decay, Func *input) { return reverb_create(dvd(param(EvalParamSustainTick), interval), decay, input); }
Func *reverb_(double interval, double decay, Func *input) { return reverb(const_(interval), const_(decay), input); }

Func *loop(Func *duration, Func *input) { return loop_create(dvd(param(EvalParamTempoTick), duration), input); }
Func *loop_(double duration, Func *input) { return loop(const_(duration), input); }

Func *delay(Func *duration, Func *input) { return delay_create(dvd(param(EvalParamTempoTick), duration), input); }
Func *delay_(double duration, Func *input) { return delay(const_(duration), input); }

Func *skip(Func *duration, Func *input) { return delay(neg(duration), input); }
Func *skip_(double duration, Func *input) { return skip(const_(duration), input); }

Func *detune(Func *derange, Func *tune, Func *input) { return pitch(add_(1, mul(derange, tune)), input); }
Func *detune_(double derange, Func *tune, Func *input) { return detune(const_(derange), tune, input); }

Func *unison(size_t count, Func *derange, Func *input) { return unison_create(count, detune(derange, sample_create(rand_create()), input)); }
Func *unison_(size_t count, double derange, Func *input) { return unison(count, const_(derange), input); }

Func *overtone(int range, Func *gain, Func *input) { return overtone_create(range, gain, input); }
Func *overtone_(int range, double gain, Func *input) { return overtone(range, const_(gain), input); }

Func *continuous(Func *input) { return continuous_create(input); }

#endif // CSYNTH_EFFECTS_H
