#ifndef CSYNTH_TIME_PLAYER_H
#define CSYNTH_TIME_PLAYER_H

#include "./player.h"

#define EXIT_KEY '\e' // ESC key

/** @brief Play channels with PortAudio output. */
csError time_player_play(double duration, size_t count, Func **channels)
{
    Player player = {0};
    csError error = player_open(&player, SAMPLE_RATE, count, channels);
    if (error != csErrorNone)
    {
        return error;
    }
#ifdef AUTO_EXIT
    duration = AUTO_EXIT * 1e-3;
#endif
    Pa_Sleep((long)(duration * 1e3));
    return player_close(&player);
}

int play_time_cleanup(double duration, size_t count, Func **channels) /* time_player_ */
{
    csError error = time_player_play(duration, count, channels);
    cleanup_all();
    return error;
}

int play_time(double duration, Func *input) { return play_time_cleanup(duration, ARGS_FUNC(input)); }                          /* time_player_ */
int play_stereo_time(double duration, Func *left, Func *right) { return play_time_cleanup(duration, ARGS_FUNC(left, right)); } /* time_player_ */

#endif // CSYNTH_TIME_PLAYER_H
