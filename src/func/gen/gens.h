//
// gens.h - Misc constants and gens
//
#ifndef CSYNTH_GENS_H
#define CSYNTH_GENS_H

#include "../../util/default.h"
#include "../op/inv.h"
#include "../time/times.h"
#include "./const.h"
#include "./crack.h"
#include "./karplus_strong.h"
#include "./saw.h"
#include "./sine.h"
#include "./square.h"
#include "./triangle.h"
#include "./wav.h"

#define ZERO_ (0.0)
#define ZERO (const_(ZERO_))

#define ONE_ (1.0)
#define ONE (const_(ONE_))

Func *sine(Func *frequency) { return sine_gen(pitch_ticker(frequency)); }
Func *sine_(double frequency) { return sine(const_(frequency)); }

Func *saw(Func *frequency) { return saw_gen(pitch_ticker(frequency)); }
Func *saw_(double frequency) { return saw(const_(frequency)); }

Func *square(Func *frequency) { return square_gen(pitch_ticker(frequency)); }
Func *square_(double frequency) { return square(const_(frequency)); }

Func *triangle(Func *frequency) { return triangle_gen(pitch_ticker(frequency)); }
Func *triangle_(double frequency) { return triangle(const_(frequency)); }

Func *karplus_strong(Func *frequency, Func *decay) { return karplus_strong_gen(pitch_ticker(frequency), sustain_ticker(decay)); }
Func *karplus_strong_(Func *frequency, double decay) { return karplus_strong(frequency, const_(decay)); }

Func *wav(const char *filename) { return wav_filename_(filename, 0, pitch_ticker_(1)); }
Func *wav_() { return wav(DEFAULT_WAV_FILENAME); }

Func *crack(Func *frequency) { return crack_gen(pitch_ticker(frequency)); }
Func *crack_(double frequency) { return crack(const_(frequency)); }

#endif // CSYNTH_GENS_H
