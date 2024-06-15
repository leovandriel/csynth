//
// midi_player.h - Samples a function and plays it using PortAudio output and PortMidi input.
//
#ifndef CSYNTH_MIDI_PLAYER_H
#define CSYNTH_MIDI_PLAYER_H

#include "../ui/midi.h"
#include "./player.h"

int play_midi(Func *root) { return player_play_cleanup(1, (Func *[]){root}, midi_loop, 0); }
int play_midi_stereo(Func *left, Func *right) { return player_play_cleanup(2, (Func *[]){left, right}, midi_loop, 0); }

#endif // CSYNTH_MIDI_PLAYER_H
