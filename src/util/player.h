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

int player_keyboard_callback(KeyboardCommand command, void *context)
{
    PaStream *stream = (PaStream *)context;
    if (command == KeyboardCommandPlay)
    {
        PaError err = Pa_StartStream(stream);
        if (err != paNoError)
            return player_error(err);
    }
    else if (command == KeyboardCommandPause)
    {
        PaError err = Pa_StopStream(stream);
        if (err != paNoError)
            return player_error(err);
    } else {
        fprintf(stderr, "Unknown command %d\n", command);
        return 1;
    }
    return 0;
}

int play_array(int count, Func **roots)
{
    Keyboard *keyboard = keyboard_create();
    PaError err = Pa_Initialize();
    if (err != paNoError)
        return player_error(err);
    Sampler *sampler = sampler_create(count, roots);
    PaStream *stream;
    err = Pa_OpenDefaultStream(&stream, 0, count, paInt16, SAMPLER_RATE, paFramesPerBufferUnspecified, player_callback, sampler);
    if (err != paNoError)
        return player_error(err);
    keyboard_set_callback(keyboard, player_keyboard_callback, stream);
    keyboard_loop(keyboard);
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        return player_error(err);
    Pa_Terminate();
    sampler_free(sampler);
    keyboard_free(keyboard);
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
