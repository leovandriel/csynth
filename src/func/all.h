//
// all.h - A single include file for all the functions.
//
#ifndef CSYNTH_ALL_H
#define CSYNTH_ALL_H

#include "./bank/banks.h"
#include "./comp/comps.h"
#include "./comp/pattern.h"
#include "./comp/seq.h"
#include "./control/actuate.h"
#include "./control/bend.h"
#include "./control/controls.h"
#include "./control/key.h"
#include "./control/keyboard.h"
#include "./control/knob.h"
#include "./control/midi_keyboard.h"
#include "./control/mute.h"
#include "./control/pad.h"
#include "./control/pause.h"
#include "./control/replay.h"
#include "./control/selector.h"
#include "./control/stepper.h"
#include "./control/track.h"
#include "./control/trigger.h"
#include "./effect/continuous.h"
#include "./effect/delay.h"
#include "./effect/effects.h"
#include "./effect/loop.h"
#include "./effect/looper.h"
#include "./effect/overtone.h"
#include "./effect/reverb.h"
#include "./effect/unison.h"
#include "./filter/adsr.h"
#include "./filter/biquad.h"
#include "./filter/chorus.h"
#include "./filter/compressor.h"
#include "./filter/distortion.h"
#include "./filter/envelopes.h"
#include "./filter/filters.h"
#include "./filter/hpf.h"
#include "./filter/limit.h"
#include "./filter/lpf.h"
#include "./filter/resonant.h"
#include "./filter/slope.h"
#include "./filter/truncate.h"
#include "./gen/const.h"
#include "./gen/crack.h"
#include "./gen/gauss.h"
#include "./gen/gens.h"
#include "./gen/karplus_strong.h"
#include "./gen/notes.h"
#include "./gen/pink.h"
#include "./gen/sample.h"
#include "./gen/saw.h"
#include "./gen/sine.h"
#include "./gen/square.h"
#include "./gen/triangle.h"
#include "./gen/uniform.h"
#include "./gen/wav.h"
#include "./op/add.h"
#include "./op/inv.h"
#include "./op/max.h"
#include "./op/min.h"
#include "./op/mul.h"
#include "./op/neg.h"
#include "./op/ops.h"
#include "./op/pow.h"
#include "./op/prod.h"
#include "./op/sin.h"
#include "./op/smooth.h"
#include "./op/step.h"
#include "./op/sum.h"
#include "./op/tanh.h"
#include "./time/scale.h"
#include "./time/ticker.h"
#include "./time/times.h"
#include "./util/dump.h"
#include "./util/fps.h"
#include "./util/gauge.h"
#include "./util/mem.h"
#include "./util/print.h"
#include "./util/record.h"
#include "./util/utils.h"
#include "./util/wrap.h"

#endif // CSYNTH_ALL_H
