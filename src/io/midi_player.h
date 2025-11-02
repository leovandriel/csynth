#ifndef CSYNTH_MIDI_PLAYER_H
#define CSYNTH_MIDI_PLAYER_H

#include "../ui/midi.h"
#include "./player.h"

#define EXIT_KEY '\e' // ESC key

/** @brief Play channels with PortAudio output. */
csError midi_player_play(size_t count, Func **channels)
{
    Player player = {0};
    csError error = player_open(&player, SAMPLE_RATE, count, channels);
    if (error != csErrorNone)
    {
        return error;
    }
    midi_loop(0.0, EXIT_KEY);
    return player_close(&player);
}

int play_midi_cleanup(size_t count, Func **channels) /* midi_player_ */
{
    csError error = midi_player_play(count, channels);
    cleanup_all();
    return error;
}

/** @brief Shorthand for `play_midi_cleanup`. */
int play_midi(Func *input) { return play_midi_cleanup(ARGS_FUNC(input)); } /* midi_player_ */

/** @brief Shorthand for `play_midi_cleanup`. */
int play_midi_stereo(Func *left, Func *right) { return play_midi_cleanup(ARGS_FUNC(left, right)); } /* midi_player_ */

#endif // CSYNTH_MIDI_PLAYER_H
