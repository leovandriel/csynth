//
// player.h - Samples a function and plays it using PortAudio.
//
#ifndef CSYNTH_PLAYER_H
#define CSYNTH_PLAYER_H

#include <portaudio.h>
#include <stdio.h>

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

int play_array(int count, Func **roots, double duration)
{
    PaError err = Pa_Initialize();
    if (err != paNoError)
        return player_error(err);
    Sampler *sampler = sampler_create(count, roots);
    PaStream *stream;
    err = Pa_OpenDefaultStream(&stream, 0, count, paInt16, SAMPLER_RATE, paFramesPerBufferUnspecified, player_callback, sampler);
    if (err != paNoError)
        return player_error(err);
    err = Pa_StartStream(stream);
    if (err != paNoError)
        return player_error(err);
    Pa_Sleep(duration * 1000);
    err = Pa_StopStream(stream);
    if (err != paNoError)
        return player_error(err);
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        return player_error(err);
    Pa_Terminate();
    sampler_free(sampler);
    return 0;
}

int play(Func *root, double duration)
{
    return play_array(1, (Func *[]){root}, duration);
}

int play_stereo(Func *left, Func *right, double duration)
{
    return play_array(2, (Func *[]){left, right}, duration);
}

#endif // CSYNTH_PLAYER_H
