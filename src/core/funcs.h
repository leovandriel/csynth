//
// funcs.h - A single include file for all the functions.
//
#ifndef CSYNTH_FUNCS_H
#define CSYNTH_FUNCS_H

#include "../func/comp/comp.h"
#include "../func/effect/delay.h"
#include "../func/effect/loop.h"
#include "../func/effect/reverb.h"
#include "../func/env/adsr.h"
#include "../func/env/smooth.h"
#include "../func/env/step.h"
#include "../func/filter/high_pass.h"
#include "../func/filter/limit.h"
#include "../func/filter/low_pass.h"
#include "../func/filter/resonate.h"
#include "../func/gen/const.h"
#include "../func/gen/karplus_strong.h"
#include "../func/gen/noise.h"
#include "../func/gen/notes.h"
#include "../func/gen/saw.h"
#include "../func/gen/sine.h"
#include "../func/gen/square.h"
#include "../func/gen/timer.h"
#include "../func/gen/triangle.h"
#include "../func/op/add.h"
#include "../func/op/inv.h"
#include "../func/op/max.h"
#include "../func/op/min.h"
#include "../func/op/mul.h"
#include "../func/op/neg.h"
#include "../func/op/power.h"
#include "../func/util/logger.h"
#include "../func/util/print.h"

void test_funcs()
{
}

#endif // CSYNTH_FUNCS_H
