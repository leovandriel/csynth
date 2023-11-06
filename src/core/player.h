//
// player.h - Samples a function and plays it using PortAudio.
//
#ifndef CSYNTH_PLAYER_H
#define CSYNTH_PLAYER_H

#include <portaudio.h>
#include <stdio.h>

#include "func.h"

#define SAMPLE_RATE 44100
#define INPUT_CHANNELS 0
#define OUTPUT_CHANNELS 1
#define FRAMES_PER_BUFFER 256

static int callback(__attribute__((unused)) const void *argBuffer, void *outputBuffer, unsigned long framesPerBuffer, __attribute__((unused)) const PaStreamCallbackTimeInfo *timeInfo, __attribute__((unused)) PaStreamCallbackFlags statusFlags, void *userData)
{
    Gen *gen = (Gen *)userData;
    float *out = (float *)outputBuffer;
    for (unsigned long frame = 0; frame < framesPerBuffer; frame++)
    {
        double output = gen_eval(gen);
        *out++ = (float)(output > 1.0 ? 1.0 : output < -1.0 ? -1.0
                                                            : output);
    }
    return 0;
}

int error(PaError err)
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
    err = Pa_OpenDefaultStream(&stream, INPUT_CHANNELS, OUTPUT_CHANNELS, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, callback, gen);
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

#endif // CSYNTH_PLAYER_H
