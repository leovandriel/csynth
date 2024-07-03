//
// banks.h - Instrument bank
//
#ifndef CSYNTH_BANKS_H
#define CSYNTH_BANKS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../filter/envelopes.h"
#include "../filter/filters.h"
#include "../gen/gens.h"
#include "../gen/sine.h"

Func *bdrum()
{
    Func *freq = linear_env_(1, 60, 30);
    return decay_(0.05, sine(freq));
}

Func *hihat()
{
    return decay_(0.05, hpf_(20000, dvd_(uniform(), 2)));
}

Func *snare()
{
    return decay_(0.05, dvd_(uniform(), 4));
}

#endif // CSYNTH_BANKS_H
