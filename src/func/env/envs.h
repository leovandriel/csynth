//
// envs.h - Misc envelopes
//
#ifndef CSYNTH_ENVS_H
#define CSYNTH_ENVS_H

#include <assert.h>

#include "../../core/func.h"
#include "../gen/const.h"
#include "../op/power.h"
#include "../op/inv.h"
#include "../gen/timer.h"

Func *decay(Func *decay) { return expo(dvd(neg(timer()), decay)); }
Func *decay_(double factor) { return decay(const_(factor)); }

void test_envs()
{
}

#endif // CSYNTH_ENVS_H
