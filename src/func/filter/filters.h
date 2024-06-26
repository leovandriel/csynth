//
// filters.h - Misc filters
//
#ifndef CSYNTH_FILTERS_H
#define CSYNTH_FILTERS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../op/ops.h"
#include "../time/times.h"
#include "./chorus.h"
#include "./compressor.h"
#include "./distortion.h"
#include "./hpf.h"
#include "./limit.h"
#include "./lpf.h"
#include "./resonant.h"
#include "./slope.h"
#include "./truncate.h"

Func *pass(Func *input, ...) { return input; }
#define zero(...) pass(ZERO, __VA_ARGS__)
#define one(...) pass(ONE, __VA_ARGS__)
#define hush(...) zero(__VA_ARGS__)

Func *lpf(Func *frequency, Func *input) { return lpf_create(pitch_ticker(frequency), input); }
Func *lpf_(double frequency, Func *input) { return lpf(const_(frequency), input); }

Func *hpf(Func *frequency, Func *input) { return hpf_create(pitch_ticker(frequency), input); }
Func *hpf_(double frequency, Func *input) { return hpf(const_(frequency), input); }

Func *resonant(Func *frequency, Func *q_factor, Func *input) { return resonant_create(pitch_ticker(frequency), q_factor, input); }
Func *resonant_(double frequency, double q_factor, Func *input) { return resonant(const_(frequency), const_(q_factor), input); }

Func *compressor(Func *threshold, Func *ratio, Func *attack, Func *release, Func *input) { return compressor_create(threshold, ratio, sustain_ticker(attack), sustain_ticker(release), input); }
Func *compressor_(double threshold, double ratio, double attack, double release, Func *input) { return compressor(const_(threshold), const_(ratio), const_(attack), const_(release), input); }

Func *chorus(Func *modulation, Func *delay, Func *depth, Func *input) { return chorus_create(modulation, delay, depth, input); }
Func *chorus_(Func *modulation, double delay, double depth, Func *input) { return chorus(modulation, const_(delay), const_(depth), input); }

Func *distortion(Func *shape, Func *input) { return distortion_create(shape, input); }
Func *distortion_(double shape, Func *input) { return distortion(const_(shape), input); }

Func *truncate(Func *duration, Func *input) { return truncate_create(sustain_ticker(duration), input); }
Func *truncate_(double duration, Func *input) { return truncate(const_(duration), input); }

Func *slope(Func *frequency, Func *input) { return slope_create(pitch_ticker(frequency), input); }
Func *slope_(double derivative, Func *input) { return slope(const_(derivative), input); }

Func *limit(Func *diff, Func *input) { return limit_create(pitch_ticker(diff), input); }
Func *limit_(double diff, Func *input) { return limit(const_(diff), input); }

#endif // CSYNTH_FILTERS_H
