//
// gens.h - Misc constants and gens
//
#ifndef CSYNTH_GENS_H
#define CSYNTH_GENS_H

#include "../op/ops.h"
#include "./const.h"
#include "./crack.h"
#include "./gauss.h"
#include "./karplus_strong.h"
#include "./param.h"
#include "./pink.h"
#include "./sample.h"
#include "./saw.h"
#include "./sine.h"
#include "./square.h"
#include "./triangle.h"
#include "./uniform.h"
#include "./wav.h"

#define ZERO_ (0.0)
#define ZERO (const_(ZERO_))

#define ONE_ (1.0)
#define ONE (const_(ONE_))

Func *sine(Func *frequency) { return sine_create(mul(param(EvalParamPitchTick), frequency)); }
Func *sine_(double frequency) { return sine(const_(frequency)); }
Func *saw(Func *frequency) { return saw_create(mul(param(EvalParamPitchTick), frequency)); }
Func *saw_(double frequency) { return saw(const_(frequency)); }
Func *square(Func *frequency) { return square_create(mul(param(EvalParamPitchTick), frequency)); }
Func *square_(double frequency) { return square(const_(frequency)); }
Func *triangle(Func *frequency) { return triangle_create(mul(param(EvalParamPitchTick), frequency)); }
Func *triangle_(double frequency) { return triangle(const_(frequency)); }

Func *karplus_strong(Func *frequency, Func *decay) { return karplus_strong_create(mul(param(EvalParamPitchTick), frequency), dvd(param(EvalParamSustainTick), decay)); }
Func *karplus_strong_(Func *frequency, double decay) { return karplus_strong(frequency, const_(decay)); }

Func *wav(const char *filename) { return wav_filename(filename, 0, param_create(EvalParamPitchTick)); }
Func *wav_() { return wav(DEFAULT_WAV_FILENAME); }

Func *uniform() { return uniform_create(); }
Func *white() { return uniform_create(); }
Func *pink() { return pink_create(); }
Func *gauss() { return gauss_create(); }
Func *sample() { return sample_create(); }
Func *crack(Func *frequency) { return crack_create(mul(param(EvalParamPitchTick), frequency)); }
Func *crack_(double frequency) { return crack(const_(frequency)); }

#endif // CSYNTH_GENS_H
