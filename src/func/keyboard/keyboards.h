//
// keyboards.h - Misc keyboard controls
//
#ifndef CSYNTH_KEYBOARDS_H
#define CSYNTH_KEYBOARDS_H

#include <math.h>

#include "../../core/func.h"
#include "../../util/error.h"
#include "../gen/gens.h"
#include "../op/ops.h"
#include "../time/times.h"
#include "./actuate.h"
#include "./mute.h"
#include "./pause.h"
#include "./replay.h"
#include "./selector.h"
#include "./stepper.h"
#include "./track.h"
#include "./trigger.h"

Func *trigger(int key, Func *input) { return trigger_create(key, input); }

Func *mute(int key, Func *input) { return mute_create(key, 0, input); }
Func *unmute(int key, Func *input) { return mute_create(key, 1, input); }

Func *pause_play(int key, Func *input) { return pause_create(key, 0, 0, input); }
Func *play_pause(int key, Func *input) { return pause_create(key, 0, 1, input); }
Func *pause_reset(int key, Func *input) { return pause_create(key, 1, 0, input); }
Func *reset_pause(int key, Func *input) { return pause_create(key, 1, 1, input); }

#define selector(key, ...) (selector_create(key, FUNCS(__VA_ARGS__)))

Func *stepper(int key, double value, double delta) { return stepper_create(key, value, delta, -FLT_MAX, FLT_MAX, 0); }
Func *stepper_rel(int key, double value, double perc) { return stepper_create(key, value, perc, -FLT_MAX, FLT_MAX, 1); }

Func *track(const char *filename, Func *input) { return track_create(filename, input); }
Func *track_(Func *input) { return track(DEFAULT_REC_FILENAME, input); }
Func *replay(const char *filename, Func *input) { return replay_create(filename, tempo_ticker_(1), input); }
Func *replay_(Func *input) { return replay(DEFAULT_REC_FILENAME, input); }

Func *actuate(int key) { return actuate_create(key); }

#endif // CSYNTH_KEYBOARDS_H
