//
// midi_player.h - Samples a function and plays it using PortAudio output and PortMIDI input.
//
#ifndef CSYNTH_MIDI_PLAYER_H
#define CSYNTH_MIDI_PLAYER_H

#include "../ui/midi.h"
#include "./player.h"

const PlayerConfig MIDI_PLAYER_CONFIG = {
    .loop = midi_loop,
    .duration = 0.0,
    .sample_rate = SAMPLE_RATE,
    .exit_key = EXIT_KEY,
};

int play_midi(Func *input) { return player_play_with_cleanup(MIDI_PLAYER_CONFIG, FUNCS(input)); }                          /* midi_player_ */
int play_midi_stereo(Func *left, Func *right) { return player_play_with_cleanup(MIDI_PLAYER_CONFIG, FUNCS(left, right)); } /* midi_player_ */

#endif // CSYNTH_MIDI_PLAYER_H
