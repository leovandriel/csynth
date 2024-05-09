//
// player.h - Samples a function and plays it using PortAudio.
//
#ifndef CSYNTH_PLAYER_H
#define CSYNTH_PLAYER_H

#include <portaudio.h>
#include <stdio.h>

#include "./sampler.h"
#include "./keyboard.h"

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
    if (Pa_IsStreamStopped(stream))
    {
        PaError err = Pa_StartStream(stream);
        if (err != paNoError)
            return player_error(err);
    }
    else
    {
        PaError err = Pa_StopStream(stream);
        if (err != paNoError)
            return player_error(err);
    }
    return 0;
}

int player_event_listener(EventType type, void *event, void *context)
{
    if (type == EventTypeKey)
    {
        int key = *(int *)event;
        if (key == ' ')
        {
            return player_play_pause((PaStream *)context);
        }
    }
    return 0;
}

int play_array(int count, Func **roots)
{
    PaError err = Pa_Initialize();
    if (err != paNoError)
        return player_error(err);
    Sampler *sampler = sampler_create(count, roots);
    PaStream *stream;
    err = Pa_OpenDefaultStream(&stream, 0, count, paInt16, SAMPLER_RATE, paFramesPerBufferUnspecified, player_callback, sampler);
    if (err != paNoError)
        return player_error(err);
    event_add_listener(player_event_listener, stream);
    err = Pa_StartStream(stream);
    if (err != paNoError)
        return player_error(err);
    keyboard_loop();
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        return player_error(err);
    Pa_Terminate();
    sampler_free(sampler);
    return 0;
}

int play(Func *root)
{
    return play_array(1, (Func *[]){root});
}

int play_stereo(Func *left, Func *right)
{
    return play_array(2, (Func *[]){left, right});
}

#endif // CSYNTH_PLAYER_H
