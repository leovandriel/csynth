//
// gens.h - Misc constants and gens
//
#ifndef CSYNTH_GENS_H
#define CSYNTH_GENS_H

#include "../effect/pitch.h"
#include "./const.h"
#include "./saw.h"
#include "./sine.h"
#include "./square.h"
#include "./triangle.h"

typedef Func *(*gen_func)(Func *frequency);

#define ZERO_ (0.0)
#define ZERO (const_(ZERO_))

#define ONE_ (1.0)
#define ONE (const_(ONE_))

Func *sine(Func *frequency) { return pitch(sine_osc(), frequency); }
Func *sine_(double frequency) { return sine(const_(frequency)); }

Func *saw(Func *frequency) { return pitch(saw_osc(), frequency); }
Func *saw_(double frequency) { return saw(const_(frequency)); }

Func *square(Func *frequency) { return pitch(square_osc(), frequency); }
Func *square_(double frequency) { return square(const_(frequency)); }

Func *triangle(Func *frequency) { return pitch(triangle_osc(), frequency); }
Func *triangle_(double frequency) { return triangle(const_(frequency)); }

#endif // CSYNTH_GENS_H
