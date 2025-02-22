#ifndef CSYNTH_TERM_PLAYER_H
#define CSYNTH_TERM_PLAYER_H

#include "../ui/terminal.h"
#include "./player.h"

#define EXIT_KEY '\e' // ESC key

/** @brief Play channels with PortAudio output. */
csError term_player_play(size_t count, Func **channels)
{
    Player player = {0};
    csError error = player_open(&player, SAMPLE_RATE, count, channels);
    if (error != csErrorNone)
    {
        return error;
    }
    terminal_loop(0.0, EXIT_KEY);
    return player_close(&player);
}

int play_channels_cleanup(size_t count, Func **channels) /* term_player_ */
{
    csError error = term_player_play(count, channels);
    cleanup_all();
    return error;
}

int play(Func *input) { return play_channels_cleanup(ARGS(input)); }                          /* term_player_ */
int play_stereo(Func *left, Func *right) { return play_channels_cleanup(ARGS(left, right)); } /* term_player_ */

#endif // CSYNTH_TERM_PLAYER_H
