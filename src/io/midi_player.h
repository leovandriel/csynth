//
// midi_player.h - Samples a function and plays it using PortAudio output and PortMIDI input.
//
#ifndef CSYNTH_MIDI_PLAYER_H
#define CSYNTH_MIDI_PLAYER_H

#include "../ui/midi.h"
#include "./player.h"

const PlayerConfig player_config_midi = {.loop = midi_loop, .duration = 0, .sample_rate = SAMPLE_RATE, .exit_key = EXIT_KEY};

int play_midi(Func *input) { return player_play_with_cleanup(player_config_midi, FUNCS(input)); }
int play_midi_stereo(Func *left, Func *right) { return player_play_with_cleanup(player_config_midi, FUNCS(left, right)); }

#endif // CSYNTH_MIDI_PLAYER_H
