//
// filters.h - Misc filters
//
#ifndef CSYNTH_FILTERS_H
#define CSYNTH_FILTERS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../op/ops.h"

Func *pass(Func *input, ...) { return input; }
#define zero(...) pass(ZERO, __VA_ARGS__)
#define one(...) pass(ONE, __VA_ARGS__)
#define hush(...) zero(__VA_ARGS__)

#endif // CSYNTH_FILTERS_H
