//
// envelopes.h - Misc envelopes
//
#ifndef CSYNTH_EFFECTS_H
#define CSYNTH_EFFECTS_H

#include "../time/times.h"
#include "./continuous.h"
#include "./delay.h"
#include "./loop.h"
#include "./looper.h"
#include "./reverb.h"

Func *reverb(Func *interval, Func *decay, Func *input) { return reverb_create(sustain_ticker(interval), decay, input); }
Func *reverb_(double interval, double decay, Func *input) { return reverb(const_(interval), const_(decay), input); }

Func *loop(Func *duration, Func *input) { return loop_create(tempo_ticker(inv(duration)), input); }
Func *loop_(double duration, Func *input) { return loop(const_(duration), input); }

Func *delay(Func *duration, Func *input) { return delay_create(tempo_ticker(inv(duration)), input); }
Func *delay_(double duration, Func *input) { return delay(const_(duration), input); }

Func *skip(Func *duration, Func *input) { return delay(neg(duration), input); }
Func *skip_(double duration, Func *input) { return skip(const_(duration), input); }

Func *looper(int key, Func *interval, Func *input) { return looper_create(key, tempo_ticker(inv(interval)), input); }
Func *looper_(int key, double interval, Func *input) { return looper(key, const_(interval), input); }

Func *continuous(Func *input) { return continuous_create(input); }

#endif // CSYNTH_EFFECTS_H
