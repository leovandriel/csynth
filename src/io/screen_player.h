#ifndef CSYNTH_SCREEN_PLAYER_H
#define CSYNTH_SCREEN_PLAYER_H

#include "../ui/screen.h"
#include "./player.h"

#define EXIT_KEY '\e' // ESC key

/** @brief Play channels with PortAudio output. */
csError screen_player_play(RenderPipe *pipe, size_t count, Func **channels)
{
    Player player = {0};
    csError error = player_open(&player, SAMPLE_RATE, count, channels);
    if (error != csErrorNone)
    {
        return error;
    }
    screen_loop(0.0, EXIT_KEY, pipe);
    return player_close(&player);
}

int play_screen_cleanup(RenderPipe *pipe, size_t count, Func **channels) /* screen_player_ */
{
    csError error = screen_player_play(pipe, count, channels);
    cleanup_all();
    return error;
}

/** @brief Shorthand for `play_screen_cleanup`. */
int play_screen(Func *input, RenderPipe *pipe) { return play_screen_cleanup(pipe, ARGS_FUNC(input)); } /* screen_player_ */

/** @brief Shorthand for `play_screen_cleanup`. */
int play_screen_stereo(Func *left, Func *right, RenderPipe *pipe) { return play_screen_cleanup(pipe, ARGS_FUNC(left, right)); } /* screen_player_ */

#endif // CSYNTH_SCREEN_PLAYER_H
