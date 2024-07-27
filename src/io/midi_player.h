#ifndef CSYNTH_MIDI_PLAYER_H
#define CSYNTH_MIDI_PLAYER_H

#include "../ui/midi.h"
#include "./player.h"

/** @brief Configuration that uses PortAudio output and PortMIDI input. */
const PlayerConfig MIDI_PLAYER_CONFIG = {
    .loop = midi_loop,
    .duration = 0.0,
    .sample_rate = SAMPLE_RATE,
    .exit_key = EXIT_KEY,
};

/** @brief Shorthand for `player_play_with_cleanup`, using MIDI_PLAYER_CONFIG.
 * */
int play_midi(Func *input) { return player_play_with_cleanup(MIDI_PLAYER_CONFIG, ARGS(input)); } /* midi_player_ */
/** @brief Shorthand for `player_play_with_cleanup`, using MIDI_PLAYER_CONFIG.
 * */
int play_midi_stereo(Func *left, Func *right) { return player_play_with_cleanup(MIDI_PLAYER_CONFIG, ARGS(left, right)); } /* midi_player_ */

#endif // CSYNTH_MIDI_PLAYER_H
