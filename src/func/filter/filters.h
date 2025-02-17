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
#include "./gamma.h"
#include "./hpf.h"
#include "./lpf.h"
#include "./resonant.h"
#include "./sample.h"
#include "./slope.h"

/** @brief Pass through input signal unchanged, ignoring additional arguments */
Func *pass(Func *input, ...) { return input; }
/** @brief Create a zero signal, ignoring additional arguments */
#define zero(...) pass(ZERO, __VA_ARGS__)
/** @brief Create a unit signal, ignoring additional arguments */
#define one(...) pass(ONE, __VA_ARGS__)
/** @brief Alias for zero() to silence a signal */
#define hush(...) zero(__VA_ARGS__)

/** @brief Create a first-order low-pass filter with variable frequency */
Func *lpf(Func *frequency, Func *input) { return lpf_create(mul(param(EvalParamPitchTick), frequency), input); }
/** @brief Create a first-order low-pass filter with constant frequency */
Func *lpf_(double frequency, Func *input) { return lpf(const_(frequency), input); }

/** @brief Create a first-order high-pass filter with variable frequency */
Func *hpf(Func *frequency, Func *input) { return hpf_create(mul(param(EvalParamPitchTick), frequency), input); }
/** @brief Create a first-order high-pass filter with constant frequency */
Func *hpf_(double frequency, Func *input) { return hpf(const_(frequency), input); }

/** @brief Create a second-order low-pass filter with variable frequency and Q factor */
Func *lowpass(Func *frequency, Func *qfactor, Func *input) { return lowpass_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
/** @brief Create a second-order low-pass filter with constant frequency and Q factor */
Func *lowpass_(double frequency, double qfactor, Func *input) { return lowpass(const_(frequency), const_(qfactor), input); }
/** @brief Create a second-order high-pass filter with variable frequency and Q factor */
Func *highpass(Func *frequency, Func *qfactor, Func *input) { return highpass_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
/** @brief Create a second-order high-pass filter with constant frequency and Q factor */
Func *highpass_(double frequency, double qfactor, Func *input) { return highpass(const_(frequency), const_(qfactor), input); }
/** @brief Create a second-order band-pass filter with variable frequency and Q factor */
Func *bandpass(Func *frequency, Func *qfactor, Func *input) { return bandpass_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
/** @brief Create a second-order band-pass filter with constant frequency and Q factor */
Func *bandpass_(double frequency, double qfactor, Func *input) { return bandpass(const_(frequency), const_(qfactor), input); }
/** @brief Create a second-order notch filter with variable frequency and Q factor */
Func *notch(Func *frequency, Func *qfactor, Func *input) { return notch_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
/** @brief Create a second-order notch filter with constant frequency and Q factor */
Func *notch_(double frequency, double qfactor, Func *input) { return notch(const_(frequency), const_(qfactor), input); }
/** @brief Create a second-order peaking filter with variable frequency, Q factor and gain */
Func *peak(Func *frequency, Func *qfactor, Func *gain, Func *input) { return peak_create(mul(param(EvalParamPitchTick), frequency), qfactor, gain, input); }
/** @brief Create a second-order peaking filter with constant frequency, Q factor and gain */
Func *peak_(double frequency, double qfactor, double gain, Func *input) { return peak(const_(frequency), const_(qfactor), const_(gain), input); }
/** @brief Create a second-order all-pass filter with variable frequency and Q factor */
Func *allpass(Func *frequency, Func *qfactor, Func *input) { return allpass_create(mul(param(EvalParamPitchTick), frequency), qfactor, input); }
/** @brief Create a second-order all-pass filter with constant frequency and Q factor */
Func *allpass_(double frequency, double qfactor, Func *input) { return allpass(const_(frequency), const_(qfactor), input); }
/** @brief Create a second-order low-shelf filter with variable frequency and gain */
Func *lowshelf(Func *frequency, Func *gain, Func *input) { return lowshelf_create(mul(param(EvalParamPitchTick), frequency), gain, input); }
/** @brief Create a second-order low-shelf filter with constant frequency and gain */
Func *lowshelf_(double frequency, double gain, Func *input) { return lowshelf(const_(frequency), const_(gain), input); }
/** @brief Create a second-order high-shelf filter with variable frequency and gain */
Func *highshelf(Func *frequency, Func *gain, Func *input) { return highshelf_create(mul(param(EvalParamPitchTick), frequency), gain, input); }
/** @brief Create a second-order high-shelf filter with constant frequency and gain */
Func *highshelf_(double frequency, double gain, Func *input) { return highshelf(const_(frequency), const_(gain), input); }

/** @brief Create a resonant filter with variable frequency and Q factor */
Func *resonant(Func *frequency, Func *q_factor, Func *input) { return resonant_create(mul(param(EvalParamPitchTick), frequency), q_factor, input); }
/** @brief Create a resonant filter with constant frequency and Q factor */
Func *resonant_(double frequency, double q_factor, Func *input) { return resonant(const_(frequency), const_(q_factor), input); }

/** @brief Create a dynamic range compressor with variable threshold, ratio, attack and release */
Func *compressor(Func *threshold, Func *ratio, Func *attack, Func *release, Func *input) { return compressor_create(threshold, ratio, dvd(param(EvalParamSustainTick), attack), dvd(param(EvalParamSustainTick), release), input); }
/** @brief Create a dynamic range compressor with constant threshold, ratio, attack and release */
Func *compressor_(double threshold, double ratio, double attack, double release, Func *input) { return compressor(const_(threshold), const_(ratio), const_(attack), const_(release), input); }

/** @brief Create a chorus effect with variable modulation, delay and depth */
Func *chorus(Func *modulation, Func *delay, Func *depth, Func *input) { return chorus_create(param(EvalParamPitchTick), modulation, delay, depth, input); }
/** @brief Create a chorus effect with variable modulation but constant delay and depth */
Func *chorus_(Func *modulation, double delay, double depth, Func *input) { return chorus(modulation, const_(delay), const_(depth), input); }

/** @brief Create a distortion effect with variable shape */
Func *distortion(Func *shape, Func *input) { return distortion_create(shape, input); }
/** @brief Create a distortion effect with constant shape */
Func *distortion_(double shape, Func *input) { return distortion(const_(shape), input); }

/** @brief Create a finish effect with variable duration */
Func *finish(Func *duration, Func *input) { return finish_create(dvd(param(EvalParamSustainTick), duration), input); }
/** @brief Create a finish effect with constant duration */
Func *finish_(double duration, Func *input) { return finish(const_(duration), input); }

/** @brief Create a slope limit with variable frequency */
Func *slope(Func *frequency, Func *input) { return slope_create(mul(param(EvalParamPitchTick), frequency), input); }
/** @brief Create a slope limit with constant derivative */
Func *slope_(double derivative, Func *input) { return slope(const_(derivative), input); }

/** @brief Maps triangle wave shape to circle */
Func *circle(Func *frequency) { return gamma_create(triangle(frequency), const_(1), map_circle); }
/** @brief Maps triangle wave shape to power */
Func *gamma(Func *input, Func *exponent) { return gamma_create(input, exponent, map_gamma); }
/** @brief Maps triangle wave shape to power */
Func *gamma_(Func *input, int exponent) { return gamma(input, _(exponent)); }

#endif // CSYNTH_FILTERS_H
