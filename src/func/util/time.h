//
// time.h - Time stuff
//
#ifndef CSYNTH_TIME_H
#define CSYNTH_TIME_H

#include "../gen/const.h"
#include "../gen/param.h"
#include "../op/ops.h"
#include "./scale.h"

Func *timer(EvalParam tick) { return sum(param_create(tick)); }

Func *pitch(Func *factor, Func *input) { return scale(EvalParamPitchTick, factor, input); }
Func *pitch_(double factor, Func *input) { return pitch(const_(factor), input); }
Func *tempo(Func *factor, Func *input) { return scale(EvalParamTempoTick, factor, input); }
Func *tempo_(double factor, Func *input) { return tempo(const_(factor), input); }
Func *sustain(Func *factor, Func *input) { return scale(EvalParamSustainTick, inv(factor), input); }
Func *sustain_(double factor, Func *input) { return sustain(const_(factor), input); }

#endif // CSYNTH_TIME_H
