//
// player.h - Samples a function and plays it using PortAudio.
//
#ifndef CSYNTH_PLAYER_H
#define CSYNTH_PLAYER_H

#include <portaudio.h>
#include <stdio.h>

#include "func.h"

static const int SAMPLE_RATE = 44100;
static const int INPUT_CHANNELS = 0;
static const int OUTPUT_CHANNELS = 1;
static const int FRAMES_PER_BUFFER = 256;

static int player_callback(__attribute__((unused)) const void *args, void *buffer, unsigned long count, __attribute__((unused)) const PaStreamCallbackTimeInfo *info, __attribute__((unused)) PaStreamCallbackFlags flags, void *data)
{
    Gen *gen = (Gen *)data;
    float *out = (float *)buffer;
    for (unsigned long frame = 0; frame < count; frame++)
    {
        double output = gen_eval(gen);
        *out++ = (float)(output > 1.0 ? 1.0 : output < -1.0 ? -1.0
                                                            : output);
    }
    return 0;
}

static int error(PaError err)
{
    fprintf(stderr, "Error %d: %s\n", err, Pa_GetErrorText(err));
    Pa_Terminate();
    return 1;
}

int play(Func *root, double duration)
{
    PaError err = Pa_Initialize();
    if (err != paNoError)
        return error(err);
    Gen *gen = gen_create(root, 1.0 / SAMPLE_RATE);
    PaStream *stream;
    err = Pa_OpenDefaultStream(&stream, INPUT_CHANNELS, OUTPUT_CHANNELS, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, player_callback, gen);
    if (err != paNoError)
        return error(err);
    err = Pa_StartStream(stream);
    if (err != paNoError)
        return error(err);
    Pa_Sleep(duration * 1000);
    err = Pa_StopStream(stream);
    if (err != paNoError)
        return error(err);
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        return error(err);
    Pa_Terminate();
    gen_free(gen);
    return 0;
}

void test_player()
{
}

#endif // CSYNTH_PLAYER_H
