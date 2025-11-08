#ifndef CSYNTH_PLAY_H
#define CSYNTH_PLAY_H

#include <stdio.h>

#include "./player_run.h"
#include "./sleep_run.h"
#include "./time_run.h"

#define PLAY_SLEEP_DURATION 0.01

/** @brief Play a function with PortAudio output.
 *
 * Adding sleeper ensure thread sleeps during loop.
 */
#define play(__inputs, ...) run_loop(player_run(__inputs), sleep_run(PLAY_SLEEP_DURATION), __VA_ARGS__)
#define play_stereo(__left, __right, ...) run_loop(player_run(__left, __right), sleep_run(PLAY_SLEEP_DURATION), __VA_ARGS__)

/** @brief Play a function with PortAudio output for a given duration.
 *
 * Adding timer and sleeper ensure thread sleeps during loop and stops after given duration.
 */
int play_time(double duration, Func *input) { return run_loop(player_run(input), time_run(duration), sleep_run(PLAY_SLEEP_DURATION)); }
int play_time_stereo(double duration, Func *left, Func *right) { return run_loop(player_run(left, right), time_run(duration), sleep_run(PLAY_SLEEP_DURATION)); }

#endif // CSYNTH_PLAY_H
