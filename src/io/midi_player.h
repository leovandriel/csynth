//
// midi_player.h - Samples a function and plays it using PortAudio output and PortMIDI input.
//
#ifndef CSYNTH_MIDI_PLAYER_H
#define CSYNTH_MIDI_PLAYER_H

#include "../ui/midi.h"
#include "./player.h"

const PlayerConfig player_config_midi = {.loop = midi_loop, .duration = 0, .sample_rate = CONFIG_DEFAULT_SAMPLE_RATE, .exit_key = CONFIG_DEFAULT_EXIT_KEY};

int play_midi(Func *root) { return player_play_with_cleanup(1, (Func *[]){root}, player_config_midi); }
int play_midi_stereo(Func *left, Func *right) { return player_play_with_cleanup(2, (Func *[]){left, right}, player_config_midi); }

#endif // CSYNTH_MIDI_PLAYER_H
