#ifndef CSYNTH_CONTROLS_H
#define CSYNTH_CONTROLS_H

#include <math.h>

#include "../../core/func.h"
#include "../../util/error.h"
#include "../filter/filters.h"
#include "../gen/gens.h"
#include "../op/ops.h"
#include "./actuate.h"
#include "./key.h"
#include "./keyboard.h"
#include "./midi_keyboard.h"
#include "./midi_value.h"
#include "./mute.h"
#include "./pad.h"
#include "./pause.h"
#include "./replay.h"
#include "./selector.h"
#include "./stepper.h"
#include "./track.h"
#include "./trigger.h"

#define DEFAULT_REC_FILENAME "output/default.rec"
#define MIDI_KEYBOARD_NOTE_COUNT 10
#define KEYBOARD_SEMITONES 12

/** @brief Shorthand for `trigger_create`. */
Func *trigger(int key, Func *input) { return trigger_create(key, input); }

/** @brief Shorthand for `mute_create`, starting unmuted. */
Func *mute(int key, Func *input) { return mute_create(key, 0, input); }
/** @brief Shorthand for `mute_create`, starting muted. */
Func *unmute(int key, Func *input) { return mute_create(key, 1, input); }

/** @brief Shorthand for `pause_create`, starting paused. */
Func *pause_play(int key, Func *input) { return pause_create(key, 0, 0, input); }
/** @brief Shorthand for `pause_create`, starting playing. */
Func *play_pause(int key, Func *input) { return pause_create(key, 0, 1, input); }
/** @brief Shorthand for `pause_create`, starting paused and reset on play. */
Func *pause_reset(int key, Func *input) { return pause_create(key, 1, 0, input); }
/** @brief Shorthand for `pause_create`, starting playing and reset on pause. */
Func *reset_pause(int key, Func *input) { return pause_create(key, 1, 1, input); }

/** @brief Shorthand for `selector_create`. */
#define selector(key, ...) (selector_create(key, ARGS(__VA_ARGS__)))

/** @brief Shorthand for `stepper_create`. */
Func *stepper(int key, double value, double delta) { return stepper_create(key, value, delta, -FLT_MAX, FLT_MAX, 0); }
/** @brief Shorthand for `stepper_create` with relative increments. */
Func *stepper_rel(int key, double value, double perc) { return stepper_create(key, value, perc, -FLT_MAX, FLT_MAX, 1); }

/** @brief Shorthand for `track_create`. */
Func *track(const char *filename, Func *input) { return track_create(filename, input); }
/** @brief Shorthand for `track_create` with default filename. */
Func *track_(Func *input) { return track(DEFAULT_REC_FILENAME, input); }

/** @brief Shorthand for `replay_create` with based on tempo tick. */
Func *replay(const char *filename, Func *input) { return replay_create(filename, param_create(EvalParamTempoTick), input); }
/** @brief Shorthand for `replay_create` with default filename and tempo tick.
 * */
Func *replay_(Func *input) { return replay(DEFAULT_REC_FILENAME, input); }

/** @brief Shorthand for `actuate_create`. */
Func *actuate(int key) { return actuate_create(key); }

/** @brief Shorthand for `midi_value_create`, based on MIDI controller, using
 * slope limiter. */
Func *knob_smooth(int channel, int control, Func *derivative) { return slope(derivative, midi_value_create(MidiTypeController, channel, control)); }
/** @brief Shorthand for `knob_smooth`, using linear interpolation. */
Func *knob(int channel, int control, Func *min, Func *max) { return linear_op(const_(1), min, max, knob_smooth(channel, control, const_(1))); }
/** @brief Shorthand for `knob_smooth`, using double arguments. */
Func *knob_(int channel, int control, double min, double max) { return knob(channel, control, const_(min), const_(max)); }
/** @brief Shorthand for `knob_smooth`, using exponential interpolation. */
Func *knob_ex(int channel, int control, Func *min, Func *max) { return exponent_op(const_(1), min, max, knob_smooth(channel, control, const_(1))); }
/** @brief Shorthand for `knob_ex`, using double arguments. */
Func *knob_ex_(int channel, int control, double min, double max) { return knob_ex(channel, control, const_(min), const_(max)); }

/** @brief Shorthand for `key_create`. */
Func *key(int channel, int pitch, Func *input) { return key_create(channel, pitch, input); }
/** @brief Shorthand for `pad_create`. */
Func *pad(int channel, int pad, Func *input) { return pad_create(channel, pad, input); }
/** @brief Shorthand for `midi_value_create`, using pitch bend and pitch tick.
 * */
Func *bend(int channel, Func *factor, Func *input) { return scale(EvalParamPitchTick, pow_op(factor, midi_value_create(MidiTypePitchBend, channel, 0)), input); }
/** @brief Shorthand for `bend`, using double arguments. */
Func *bend_(int channel, double factor, Func *input) { return bend(channel, const_(factor), input); }

/** @brief Shorthand for `keyboard_create`, using KEYBOARD_SEMITONES. */
Func *keyboard(keyboard_control_func control, Func *input) { return keyboard_create(KEYBOARD_SEMITONES, control, input); }
/** @brief Shorthand for `keyboard_create`, using MIDI_KEYBOARD_NOTE_COUNT. */
Func *midi_keyboard(int channel, Func *input) { return midi_keyboard_count(channel, KEYBOARD_SEMITONES, MIDI_KEYBOARD_NOTE_COUNT, input); }

#endif // CSYNTH_CONTROLS_H
