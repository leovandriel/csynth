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

typedef int (*player_event_loop)(double duration);

int player_event_loop_no_terminal(double duration)
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
    state_event_broadcast(CONFIG_PAUSE_KEY, StateEventTypeBool, &paused);
    return 0;
}

int player_event_listener(EventType type, void *event, void *context)
{
    if (type == EventTypeKey)
    {
        int key = *(int *)event;
        if (key == CONFIG_PAUSE_KEY)
        {
            return player_play_pause((PaStream *)context);
        }
    }
    return 0;
}

int player_play_channels_no_cleanup(int count, Func **channels, player_event_loop loop, double duration)
{
    PaError err = Pa_Initialize();
    if (err != paNoError)
    {
        return player_error(err);
    }
    display_show();
    state_event_broadcast(CONFIG_PAUSE_KEY, StateEventTypeBoolInv, NULL);
    Sampler *sampler = sampler_create(count, channels);
    PaStream *stream = NULL;
    err = Pa_OpenDefaultStream(&stream, 0, count, paInt16, SAMPLE_RATE, paFramesPerBufferUnspecified, player_callback, sampler);
    if (err != paNoError)
    {
        return player_error(err);
    }
    err = Pa_StartStream(stream);
    if (err != paNoError)
    {
        return player_error(err);
    }
    void *handler = event_add_listener(player_event_listener, stream);
    loop(duration);
    event_remove_listener(handler);
    err = Pa_CloseStream(stream);
    if (err != paNoError)
    {
        return player_error(err);
    }
    display_hide();
    Pa_Terminate();
    sampler_free(sampler);
    return 0;
}

int player_play_cleanup(int count, Func **channels, player_event_loop loop, double duration)
{
    int err = player_play_channels_no_cleanup(count, channels, loop, duration);
    cleanup_all();
    return err;
}

int play_duration(Func *root, double duration) { return player_play_cleanup(1, (Func *[]){root}, terminal_loop, duration); }
int play(Func *root) { return play_duration(root, 0); }
int play_(Func *root, double duration) { return play_duration(root, duration); }
int play_stereo_duration(Func *left, Func *right, double duration) { return player_play_cleanup(2, (Func *[]){left, right}, terminal_loop, duration); }
int play_stereo(Func *left, Func *right) { return play_stereo_duration(left, right, 0); }

int play_duration_no_terminal(Func *root, double duration) { return player_play_cleanup(1, (Func *[]){root}, player_event_loop_no_terminal, duration); }
int play_no_terminal(Func *root) { return play_duration_no_terminal(root, 0); }
int play_no_terminal_(Func *root, double duration) { return play_duration_no_terminal(root, duration); }
int play_stereo_duration_no_terminal(Func *left, Func *right, double duration) { return player_play_cleanup(2, (Func *[]){left, right}, player_event_loop_no_terminal, duration); }
int play_stereo_no_terminal(Func *left, Func *right) { return play_stereo_duration_no_terminal(left, right, 0); }

#endif // CSYNTH_PLAYER_H
