#ifndef CSYNTH_FILTERS_H
#define CSYNTH_FILTERS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../gen/gens.h"
#include "../op/ops.h"
#include "../util/times.h"
#include "./biquad.h"
#include "./chorus.h"
#include "./compressor.h"
#include "./distortion.h"
#include "./finish.h"
#include "./hpf.h"
#include "./lpf.h"
#include "./resonant.h"
#include "./sample.h"
#include "./slope.h"

Func *pass(Func *input, ...) { return input; }
#define zero(...) pass(ZERO, __VA_ARGS__)
#define one(...) pass(ONE, __VA_ARGS__)
#define hush(...) zero(__VA_ARGS__)

Func *lpf(Func *frequency, Func *input) { return lpf_create(mul(param(EvalParamPitchTick), frequency), input); }
Func *lpf_(double frequency, Func *input) { return lpf(const_(frequency), input); }

Func *hpf(Func *frequency, Func *input) { return hpf_create(mul(param(EvalParamPitchTick), frequency), input); }
Func *hpf_(double frequency, Func *input) { return hpf(const_(frequency), input); }

Func *lowpass(Func *frequency, Func *qfactor, Func *input) { return lowpass_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
Func *lowpass_(double frequency, double qfactor, Func *input) { return lowpass(const_(frequency), const_(qfactor), input); }
Func *highpass(Func *frequency, Func *qfactor, Func *input) { return highpass_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
Func *highpass_(double frequency, double qfactor, Func *input) { return highpass(const_(frequency), const_(qfactor), input); }
Func *bandpass(Func *frequency, Func *qfactor, Func *input) { return bandpass_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
Func *bandpass_(double frequency, double qfactor, Func *input) { return bandpass(const_(frequency), const_(qfactor), input); }
Func *notch(Func *frequency, Func *qfactor, Func *input) { return notch_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
Func *notch_(double frequency, double qfactor, Func *input) { return notch(const_(frequency), const_(qfactor), input); }
Func *peak(Func *frequency, Func *qfactor, Func *gain, Func *input) { return peak_create(mul(param(EvalParamPitchTick), frequency), qfactor, gain, input); }
Func *peak_(double frequency, double qfactor, double gain, Func *input) { return peak(const_(frequency), const_(qfactor), const_(gain), input); }
Func *allpass(Func *frequency, Func *qfactor, Func *input) { return allpass_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
Func *allpass_(double frequency, double qfactor, Func *input) { return allpass(const_(frequency), const_(qfactor), input); }
Func *lowshelf(Func *frequency, Func *gain, Func *input) { return lowshelf_create(mul(param(EvalParamPitchTick), frequency), gain, input); }
Func *lowshelf_(double frequency, double gain, Func *input) { return lowshelf(const_(frequency), const_(gain), input); }
Func *highshelf(Func *frequency, Func *gain, Func *input) { return highshelf_create(mul(param(EvalParamPitchTick), frequency), gain, input); }
Func *highshelf_(double frequency, double gain, Func *input) { return highshelf(const_(frequency), const_(gain), input); }

Func *resonant(Func *frequency, Func *q_factor, Func *input) { return resonant_create(mul(param(EvalParamPitchTick), frequency), q_factor, input); }
Func *resonant_(double frequency, double q_factor, Func *input) { return resonant(const_(frequency), const_(q_factor), input); }

Func *compressor(Func *threshold, Func *ratio, Func *attack, Func *release, Func *input) { return compressor_create(threshold, ratio, dvd(param(EvalParamSustainTick), attack), dvd(param(EvalParamSustainTick), release), input); }
Func *compressor_(double threshold, double ratio, double attack, double release, Func *input) { return compressor(const_(threshold), const_(ratio), const_(attack), const_(release), input); }

Func *chorus(Func *modulation, Func *delay, Func *depth, Func *input) { return chorus_create(param(EvalParamPitchTick), modulation, delay, depth, input); }
Func *chorus_(Func *modulation, double delay, double depth, Func *input) { return chorus(modulation, const_(delay), const_(depth), input); }

Func *distortion(Func *shape, Func *input) { return distortion_create(shape, input); }
Func *distortion_(double shape, Func *input) { return distortion(const_(shape), input); }

Func *finish(Func *duration, Func *input) { return finish_create(dvd(param(EvalParamSustainTick), duration), input); }
Func *finish_(double duration, Func *input) { return finish(const_(duration), input); }

Func *slope(Func *frequency, Func *input) { return slope_create(mul(param(EvalParamPitchTick), frequency), input); }
Func *slope_(double derivative, Func *input) { return slope(const_(derivative), input); }

#endif // CSYNTH_FILTERS_H
