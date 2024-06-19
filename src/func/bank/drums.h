//
// drums.h - Drumss
//
#ifndef CSYNTH_DRUMS_H
#define CSYNTH_DRUMS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../filter/envelopes.h"
#include "../filter/hpf.h"
#include "../gen/sine.h"
#include "../gen/uniform.h"

Func *bdrum()
{
    Func *freq = linear_env_(60, 30, 1);
    return decay_(sine(freq), .05);
}

Func *hihat()
{
    return decay_(hpf_(dvd_(uniform(), 2), 20000), .05);
}

Func *snare()
{
    return decay_(dvd_(uniform(), 4), .05);
}

#endif // CSYNTH_DRUMS_H
