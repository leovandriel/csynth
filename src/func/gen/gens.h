//
// gens.h - Misc constants and gens
//
#ifndef CSYNTH_GENS_H
#define CSYNTH_GENS_H

#include "./const.h"

typedef Func *(*gen_func)(Func *frequency);

#define ZERO_ (0.0)
#define ZERO (const_(ZERO_))

#define ONE_ (1.0)
#define ONE (const_(ONE_))

#endif // CSYNTH_GENS_H
