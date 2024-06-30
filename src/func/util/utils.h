//
// utils.h - Utils
//
#ifndef CSYNTH_UTILS_H
#define CSYNTH_UTILS_H

#include "../op/inv.h"
#include "../time/times.h"
#include "./gauge.h"

Func *gauge(const char *label, Func *input) { return gauge_interval(label, ticker_(EvalTickDisplay, 1), input); }

#endif // CSYNTH_UTILS_H
