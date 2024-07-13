//
// envelopes.h - Misc envelopes
//
#ifndef CSYNTH_EFFECTS_H
#define CSYNTH_EFFECTS_H

#include "../gen/gens.h"
#include "./continuous.h"
#include "./delay.h"
#include "./loop.h"
#include "./looper.h"
#include "./reverb.h"

Func *reverb(Func *interval, Func *decay, Func *input) { return reverb_create(dvd(param(EvalParamSustainTick), interval), decay, input); }
Func *reverb_(double interval, double decay, Func *input) { return reverb(const_(interval), const_(decay), input); }

Func *loop(Func *duration, Func *input) { return loop_create(dvd(param(EvalParamTempoTick), duration), input); }
Func *loop_(double duration, Func *input) { return loop(const_(duration), input); }

Func *delay(Func *duration, Func *input) { return delay_create(dvd(param(EvalParamTempoTick), duration), input); }
Func *delay_(double duration, Func *input) { return delay(const_(duration), input); }

Func *skip(Func *duration, Func *input) { return delay(neg(duration), input); }
Func *skip_(double duration, Func *input) { return skip(const_(duration), input); }

Func *looper_keyboard(int key, Func *interval, Func *input) { return looper_keyboard_create(key, dvd(param(EvalParamTempoTick), interval), input); }
Func *looper_keyboard_(int key, double interval, Func *input) { return looper_keyboard(key, const_(interval), input); }
Func *looper_midi(int channel, int control, Func *interval, Func *input) { return looper_midi_create(channel, control, dvd(param(EvalParamTempoTick), interval), input); }
Func *looper_midi_(int channel, int control, double interval, Func *input) { return looper_midi(channel, control, const_(interval), input); }

Func *continuous(Func *input) { return continuous_create(input); }

#endif // CSYNTH_EFFECTS_H
