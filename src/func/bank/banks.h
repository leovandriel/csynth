#ifndef CSYNTH_BANKS_H
#define CSYNTH_BANKS_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../effect/effects.h"
#include "../filter/envelopes.h"
#include "../filter/filters.h"
#include "../gen/gens.h"
#include "../gen/sine.h"

/** @brief Create a kick drum sound.  */
Func *bdrum(void)
{
    Func *freq = linear_env_(1, 60, 30);
    return decay_(0.05, sine(freq));
}

/** @brief Create a hihat sound. */
Func *hihat(void)
{
    return decay_(0.05, hpf_(20000, dvd_(white(), 2)));
}

/** @brief Create a snare drum sound. */
Func *snare(void)
{
    return decay_(0.05, dvd_(white(), 4));
}

Func *boards(Func *frequency)
{
    return detune_(.005, sine_(.03), triangle(frequency));
}

#endif // CSYNTH_BANKS_H
