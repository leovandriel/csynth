//
// filters.h - Misc filters
//
#ifndef CSYNTH_FILTERS_H
#define CSYNTH_FILTERS_H

#include "../../core/func.h"
#include "../op/ops.h"

Func *distort(Func *f, Func *multiplier) { return clamp_(mul(f, multiplier), -1, 1); }
Func *distort_(Func *f, double multiplier) { return clamp_(mul_(f, multiplier), -1, 1); }

#endif // CSYNTH_FILTERS_H
