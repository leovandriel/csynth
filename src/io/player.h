//
// player.h - Samples a function and plays it using PortAudio.
//
#ifndef CSYNTH_PLAYER_H
#define CSYNTH_PLAYER_H

#include <portaudio.h>
#include <stdio.h>

#include "../ui/display.h"
#include "../ui/term.h"
#include "./sampler.h"

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
    int paused = Pa_IsStreamStopped(stream);
    if (paused == 1)
    {
        PaError err = Pa_StartStream(stream);
        if (err != paNoError)
            return player_error(err);
    }
    else if (paused == 0)
    {
        PaError err = Pa_StopStream(stream);
        if (err != paNoError)
            return player_error(err);
    }
    else
    {
        return paused;
    }
    state_event_broadcast(config_pause_key, StateEventTypeBool, &paused);
    return 0;
}

int player_event_listener(EventType type, void *event, void *context)
{
    if (type == EventTypeKey)
    {
        int key = *(int *)event;
        if (key == config_pause_key)
        {
            return player_play_pause((PaStream *)context);
        }
    }
    return 0;
}

int play_array(int count, Func **roots, double duration)
{
    PaError err = Pa_Initialize();
    if (err != paNoError)
        return player_error(err);
    display_show();
    state_event_broadcast(config_pause_key, StateEventTypeBoolInv, NULL);
    Sampler *sampler = sampler_create(count, roots);
    PaStream *stream;
    err = Pa_OpenDefaultStream(&stream, 0, count, paInt16, SAMPLER_RATE, paFramesPerBufferUnspecified, player_callback, sampler);
    if (err != paNoError)
        return player_error(err);
    err = Pa_StartStream(stream);
    if (err != paNoError)
        return player_error(err);
    void *handler = event_add_listener(player_event_listener, stream);
    term_loop(duration);
    event_remove_listener(handler);
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        return player_error(err);
    display_hide();
    Pa_Terminate();
    sampler_free(sampler);
    return 0;
}

int play_duration(Func *root, double duration)
{
    return play_array(1, (Func *[]){root}, duration);
}

int play_stereo_duration(Func *left, Func *right, double duration)
{
    return play_array(2, (Func *[]){left, right}, duration);
}

int play(Func *root) { return play_duration(root, 0); }
int play_mono_duration(Func *input, double duration) { return play_duration(input, duration); }
int play_mono(Func *input) { return play(input); }
int play_stereo(Func *left, Func *right) { return play_stereo_duration(left, right, 0); }

#endif // CSYNTH_PLAYER_H
