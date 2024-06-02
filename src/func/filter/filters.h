//
// filters.h - Misc filters
//
#ifndef CSYNTH_FILTERS_H
#define CSYNTH_FILTERS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../op/ops.h"

Func *distort(Func *f, Func *multiplier) { return clamp_(mul(f, multiplier), -1, 1); }
Func *distort_(Func *f, double multiplier) { return clamp_(mul_(f, multiplier), -1, 1); }

Func *pass(Func *f, ...) { return f; }
#define zero(...) pass(ZERO, __VA_ARGS__)
#define one(...) pass(ONE, __VA_ARGS__)

#endif // CSYNTH_FILTERS_H
