#ifndef CSYNTH_GENS_H
#define CSYNTH_GENS_H

#include "../op/ops.h"
#include "./const.h"
#include "./crack.h"
#include "./gauss.h"
#include "./karplus_strong.h"
#include "./param.h"
#include "./pink.h"
#include "./rand.h"
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

/** @brief Create a sine wave oscillator with variable frequency */
Func *sine(Func *frequency) { return sine_create(mul(param(EvalParamPitchTick), frequency)); }
/** @brief Create a sine wave oscillator with constant frequency */
Func *sine_(double frequency) { return sine(const_(frequency)); }
/** @brief Create a sawtooth wave oscillator with variable frequency */
Func *saw(Func *frequency) { return saw_create(mul(param(EvalParamPitchTick), frequency)); }
/** @brief Create a sawtooth wave oscillator with constant frequency */
Func *saw_(double frequency) { return saw(const_(frequency)); }
/** @brief Create a square wave oscillator with variable frequency */
Func *square(Func *frequency) { return square_create(mul(param(EvalParamPitchTick), frequency)); }
/** @brief Create a square wave oscillator with constant frequency */
Func *square_(double frequency) { return square(const_(frequency)); }
/** @brief Create a triangle wave oscillator with variable frequency */
Func *triangle_skew(Func *frequency, Func *skew) { return triangle_create(mul(param(EvalParamPitchTick), frequency), skew); }
/** @brief Create a triangle wave oscillator with variable frequency */
Func *triangle_skew_(Func *frequency, double skew) { return triangle_skew(frequency, const_(skew)); }
/** @brief Create a triangle wave oscillator with variable frequency */
Func *triangle(Func *frequency) { return triangle_skew(frequency, const_(0)); }
/** @brief Create a triangle wave oscillator with constant frequency */
Func *triangle_(double frequency) { return triangle(const_(frequency)); }

/** @brief Create a Karplus-Strong string model with variable frequency and decay */
Func *karplus_strong(Func *frequency, Func *decay) { return karplus_strong_create(mul(param(EvalParamPitchTick), frequency), dvd(param(EvalParamSustainTick), decay)); }
/** @brief Create a Karplus-Strong string model with variable frequency and constant decay */
Func *karplus_strong_(Func *frequency, double decay) { return karplus_strong(frequency, const_(decay)); }

/** @brief Create a WAV file player with custom filename */
Func *wav(const char *filename) { return wav_filename(filename, 0, param_create(EvalParamPitchTick)); }
/** @brief Create a WAV file player with default filename */
Func *wav_(void) { return wav(DEFAULT_WAV_FILENAME); }

/** @brief Create a white noise generator */
Func *white(void) { return uniform_create(); }
/** @brief Create a pink noise generator */
Func *pink(void) { return pink_create(); }
/** @brief Create a Gaussian noise generator */
Func *gauss(void) { return gauss_create(); }
/** @brief Create a crackle generator with variable frequency */
Func *crack(Func *frequency) { return crack_create(mul(param(EvalParamPitchTick), frequency)); }
/** @brief Create a crackle generator with constant frequency */
Func *crack_(double frequency) { return crack(const_(frequency)); }

#endif // CSYNTH_GENS_H
