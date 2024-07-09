//
// times.h - Time stuff
//
#ifndef CSYNTH_TIMES_H
#define CSYNTH_TIMES_H

#include "../gen/const.h"
#include "../op/ops.h"
#include "./scale.h"
#include "./ticker.h"

Func *scale(EvalTick tick, Func *factor, Func *input) { return scale_create(tick, factor, input); }
Func *scale_(EvalTick tick, double factor, Func *input) { return scale(tick, const_(factor), input); }

Func *ticker(EvalTick tick, Func *factor) { return scale(tick, factor, ticker_create(tick)); }
Func *ticker_(EvalTick tick, double factor) { return ticker(tick, const_(factor)); }

Func *timer(EvalTick tick, Func *increment) { return sum(ticker(tick, increment)); }
Func *timer_(EvalTick tick, double increment) { return timer(tick, const_(increment)); }

Func *pitch_ticker(Func *factor) { return ticker(EvalTickPitch, factor); }
Func *pitch_ticker_(double factor) { return pitch_ticker(const_(factor)); }
Func *pitch_timer(Func *factor) { return timer(EvalTickPitch, factor); }
Func *pitch_timer_(double factor) { return pitch_timer(const_(factor)); }
Func *pitch(Func *factor, Func *input) { return scale(EvalTickPitch, factor, input); }
Func *pitch_(double factor, Func *input) { return pitch(const_(factor), input); }

Func *tempo_ticker(Func *scale) { return ticker(EvalTickTempo, scale); }
Func *tempo_ticker_(double scale) { return tempo_ticker(const_(scale)); }
Func *tempo_timer(Func *scale) { return timer(EvalTickTempo, scale); }
Func *tempo_timer_(double scale) { return tempo_timer(const_(scale)); }
Func *tempo(Func *factor, Func *input) { return scale(EvalTickTempo, factor, input); }
Func *tempo_(double factor, Func *input) { return tempo(const_(factor), input); }

Func *sustain_ticker(Func *scale) { return ticker(EvalTickSustain, inv(scale)); }
Func *sustain_ticker_(double scale) { return sustain_ticker(const_(scale)); }
Func *sustain_timer(Func *scale) { return timer(EvalTickSustain, inv(scale)); }
Func *sustain_timer_(double scale) { return sustain_timer(const_(scale)); }
Func *sustain(Func *factor, Func *input) { return scale(EvalTickSustain, inv(factor), input); }
Func *sustain_(double factor, Func *input) { return sustain(const_(factor), input); }

#endif // CSYNTH_TIMES_H
