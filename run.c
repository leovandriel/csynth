#include <stdio.h>
#include <math.h>
#include "portaudio.h"

#define INPUT_CHANNELS 0
#define OUTPUT_CHANNELS 1
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256
#define DURATION_SECONDS 10

#define CYCLE_SECONDS 4

typedef struct
{
    unsigned long long index;
} UserData;

static int callback(__attribute__((unused)) const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, __attribute__((unused)) const PaStreamCallbackTimeInfo *timeInfo, __attribute__((unused)) PaStreamCallbackFlags statusFlags, void *userData)
{
    UserData *data = (UserData *)userData;
    float *out = (float *)outputBuffer;
    for (unsigned int frame = 0; frame < framesPerBuffer; frame++)
    {
        float t = data->index / (float)SAMPLE_RATE;
        float phase = 0;
        float time = fmodf(t + phase, (float)CYCLE_SECONDS);
        float fade = (1 - cosf(2 * M_PI * time / CYCLE_SECONDS)) / 2;
        float frequency = 440 + 440 * time / CYCLE_SECONDS;
        float amplitude = sinf(2 * M_PI * frequency * time) * fade;
        *out++ = amplitude;
        data->index++;
    }
    return 0;
}

int error(PaError err)
{
    fprintf(stderr, "Error %d: %s\n", err, Pa_GetErrorText(err));
    Pa_Terminate();
    return 1;
}

int main(void)
{
    PaError err = Pa_Initialize();
    if (err != paNoError)
        return error(err);
    PaStream *stream;
    UserData data = {0};
    err = Pa_OpenDefaultStream(&stream, INPUT_CHANNELS, OUTPUT_CHANNELS, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, callback, &data);
    if (err != paNoError)
        return error(err);
    err = Pa_StartStream(stream);
    if (err != paNoError)
        return error(err);
    Pa_Sleep(DURATION_SECONDS * 1000);
    err = Pa_StopStream(stream);
    if (err != paNoError)
        return error(err);
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        return error(err);
    Pa_Terminate();
    return 0;
}
