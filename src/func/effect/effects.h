//
// envelopes.h - Misc envelopes
//
#ifndef CSYNTH_EFFECTS_H
#define CSYNTH_EFFECTS_H

#include "./delay.h"

Func *skip(Func *input, Func *duration) { return delay(input, neg(duration)); }
Func *skip_(Func *input, double duration) { return skip(input, const_(duration)); }

#endif // CSYNTH_EFFECTS_H
