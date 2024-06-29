//
// times.h - Time stuff
//
#ifndef CSYNTH_TIMES_H
#define CSYNTH_TIMES_H

#include "../op/inv.h"
#include "./scale.h"
#include "./tick.h"

Func *pitch_tick() { return tick(EvalTickPitch); }
Func *tempo_tick() { return tick(EvalTickTempo); }
Func *sustain_tick() { return tick(EvalTickSustain); }

Func *pitch(Func *factor, Func *input) { return scale(EvalTickPitch, factor, input); }
Func *pitch_(double factor, Func *input) { return pitch(const_(factor), input); }

Func *tempo(Func *factor, Func *input) { return scale(EvalTickTempo, factor, input); }
Func *tempo_(double factor, Func *input) { return tempo(const_(factor), input); }

Func *sustain(Func *factor, Func *input) { return scale(EvalTickSustain, inv(factor), input); }
Func *sustain_(double factor, Func *input) { return sustain(const_(factor), input); }

#endif // CSYNTH_TIMES_H
