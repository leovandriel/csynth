//
// gens.h - Misc constants and gens
//
#ifndef CSYNTH_GENS_H
#define CSYNTH_GENS_H

#include "../op/inv.h"
#include "../time/times.h"
#include "./const.h"
#include "./karplus_strong.h"
#include "./saw.h"
#include "./sine.h"
#include "./square.h"
#include "./triangle.h"

typedef Func *(*gen_func)(Func *frequency);

#define ZERO_ (0.0)
#define ZERO (const_(ZERO_))

#define ONE_ (1.0)
#define ONE (const_(ONE_))

Func *sine(Func *frequency) { return pitch(frequency, sine_osc(pitch_tick())); }
Func *sine_(double frequency) { return sine(const_(frequency)); }

Func *saw(Func *frequency) { return pitch(frequency, saw_osc(pitch_tick())); }
Func *saw_(double frequency) { return saw(const_(frequency)); }

Func *square(Func *frequency) { return pitch(frequency, square_osc(pitch_tick())); }
Func *square_(double frequency) { return square(const_(frequency)); }

Func *triangle(Func *frequency) { return pitch(frequency, triangle_osc(pitch_tick())); }
Func *triangle_(double frequency) { return triangle(const_(frequency)); }

Func *karplus_strong(Func *frequency, Func *decay) { return sustain(decay, pitch(frequency, karplus_strong_osc(pitch_tick(), sustain_tick()))); }
Func *karplus_strong_(Func *frequency, double decay) { return karplus_strong(frequency, const_(decay)); }

#endif // CSYNTH_GENS_H
