//
// player.h - Samples a function and plays it using PortAudio.
//
#ifndef CSYNTH_PLAYER_H
#define CSYNTH_PLAYER_H

#include <portaudio.h>
#include <stdio.h>

#include "../ui/display.h"
#include "../ui/terminal.h"
#include "../util/cleanup.h"
#include "./sampler.h"

typedef int (*player_event_loop)(double duration, int exit_key);

typedef struct
{
    player_event_loop loop;
    double duration;
    int sample_rate;
    int exit_key;
} PlayerConfig;

int player_event_loop_no_terminal(double duration, __attribute__((unused)) int exit_key)
{
    if (duration <= 0)
    {
        duration = FLT_MAX;
    }
    Pa_Sleep((long)(duration * 1000));
    return 0;
}

static int player_callback(__attribute__((unused)) const void *input, void *output_, unsigned long count, __attribute__((unused)) const PaStreamCallbackTimeInfo *info, __attribute__((unused)) PaStreamCallbackFlags flags, void *data)
{
    sampler_sample((Sampler *)data, count, (int16_t *)output_);
    return paContinue;
}

static int player_error(PaError err)
{
    fprintf(stderr, "Error %d: %s\n", err, Pa_GetErrorText(err));
    Pa_Terminate();
    return 1;
}

int player_play_pause(PaStream *stream)
{
    PaError paused = Pa_IsStreamStopped(stream);
    if (paused == 1)
    {
        PaError err = Pa_StartStream(stream);
        if (err != paNoError)
        {
            return player_error(err);
        }
    }
    else if (paused == 0)
    {
        PaError err = Pa_StopStream(stream);
        if (err != paNoError)
        {
            return player_error(err);
        }
    }
    else
    {
        return paused;
    }
    return 0;
}

int player_play_channels_no_cleanup(int count, Func **channels, PlayerConfig config)
{
    PaError err = Pa_Initialize();
    if (err != paNoError)
    {
        return player_error(err);
    }
    Sampler *sampler = sampler_create(count, channels, config.sample_rate);
    PaStream *stream = NULL;
    err = Pa_OpenDefaultStream(&stream, 0, count, paInt16, config.sample_rate, paFramesPerBufferUnspecified, player_callback, sampler);
    if (err != paNoError)
    {
        Pa_Terminate();
        return player_error(err);
    }
    err = Pa_StartStream(stream);
    if (err != paNoError)
    {
        Pa_CloseStream(stream);
        Pa_Terminate();
        return player_error(err);
    }
    display_show();
    config.loop(config.duration, config.exit_key);
    display_hide();
    err = Pa_CloseStream(stream);
    if (err != paNoError)
    {
        Pa_Terminate();
        return player_error(err);
    }
    sampler_free(sampler);
    err = Pa_Terminate();
    return err;
}

int player_play_with_cleanup(int count, Func **channels, PlayerConfig config)
{
    int err = player_play_channels_no_cleanup(count, channels, config);
    cleanup_all();
    return err;
}

const PlayerConfig player_config_terminal = {.loop = terminal_loop, .duration = 0, .sample_rate = CONFIG_DEFAULT_SAMPLE_RATE, .exit_key = CONFIG_DEFAULT_EXIT_KEY};
const PlayerConfig player_config_no_terminal = {.loop = player_event_loop_no_terminal, .duration = 0, .sample_rate = CONFIG_DEFAULT_SAMPLE_RATE, .exit_key = CONFIG_DEFAULT_EXIT_KEY};

int play(Func *root) { return player_play_with_cleanup(1, (Func *[]){root}, player_config_terminal); }
int play_stereo(Func *left, Func *right) { return player_play_with_cleanup(2, (Func *[]){left, right}, player_config_terminal); }

int play_duration(Func *root, double duration) { return player_play_with_cleanup(1, (Func *[]){root}, (PlayerConfig){player_event_loop_no_terminal, duration, CONFIG_DEFAULT_SAMPLE_RATE, CONFIG_DEFAULT_EXIT_KEY}); }
int play_(Func *root, double duration) { return play_duration(root, duration); }
int play_stereo_duration(Func *left, Func *right, double duration) { return player_play_with_cleanup(2, (Func *[]){left, right}, (PlayerConfig){player_event_loop_no_terminal, duration, CONFIG_DEFAULT_SAMPLE_RATE, CONFIG_DEFAULT_EXIT_KEY}); }

#endif // CSYNTH_PLAYER_H
