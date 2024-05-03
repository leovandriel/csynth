//
// all.h - A single include file for all the functions.
//
#ifndef CSYNTH_FUNC_ALL_H
#define CSYNTH_FUNC_ALL_H

#include "./comp/comp.h"
#include "./effect/continuous.h"
#include "./effect/delay.h"
#include "./effect/loop.h"
#include "./effect/reverb.h"
#include "./env/adsr.h"
#include "./env/envs.h"
#include "./env/smooth.h"
#include "./env/step.h"
#include "./filter/chorus.h"
#include "./filter/high_pass.h"
#include "./filter/limit.h"
#include "./filter/low_pass.h"
#include "./filter/resonant.h"
#include "./gen/const.h"
#include "./gen/karplus_strong.h"
#include "./gen/noise.h"
#include "./gen/notes.h"
#include "./gen/saw.h"
#include "./gen/sine.h"
#include "./gen/square.h"
#include "./gen/timer.h"
#include "./gen/triangle.h"
#include "./op/add.h"
#include "./op/inv.h"
#include "./op/max.h"
#include "./op/min.h"
#include "./op/mul.h"
#include "./op/neg.h"
#include "./op/ops.h"
#include "./op/power.h"
#include "./util/callback.h"
#include "./util/logger.h"
#include "./util/print.h"

void test_all()
{
}

#endif // CSYNTH_FUNC_ALL_H
