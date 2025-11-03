#ifndef CSYNTH_PLAYER_H
#define CSYNTH_PLAYER_H

#include <portaudio.h>
#include <stdio.h>

#include "../event/event.h"
#include "../util/logger.h"
#include "./sampler.h"

typedef struct
{
    Sampler *sampler;
    PaStream *stream;
} Player;

static int player_callback(__U const void *input, void *output_, size_t count, __U const PaStreamCallbackTimeInfo *info, __U PaStreamCallbackFlags flags, void *data)
{
    sampler_sample((Sampler *)data, count, (int16_t *)output_);
    return paContinue;
}

csError player_play_pause(PaStream *stream)
{
    PaError paused = Pa_IsStreamStopped(stream);
    if (paused == 1)
    {
        PaError pa_error = Pa_StartStream(stream);
        if (pa_error != paNoError)
        {
            return error_type_message(csErrorPortAudio, "Unable to start stream: %s", Pa_GetErrorText(pa_error), pa_error);
        }
    }
    else if (paused == 0)
    {
        PaError pa_error = Pa_StopStream(stream);
        if (pa_error != paNoError)
        {
            return error_type_message(csErrorPortAudio, "Unable to stop stream: %s", Pa_GetErrorText(pa_error), pa_error);
        }
    }
    else
    {
        return paused;
    }
    return csErrorNone;
}

/** @brief Play channels with PortAudio output. */
csError player_open(Player *player, size_t sample_rate, size_t count, Func **channels)
{
    PaError pa_error = Pa_Initialize();
    if (pa_error != paNoError)
    {
        return error_type_message(csErrorPortAudio, "Unable to initialize: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    PaDeviceIndex device = Pa_GetDefaultOutputDevice();
    if (device == paNoDevice)
    {
        Pa_Terminate();
        return error_type_message(csErrorInit, "No default audio device");
    }
    const PaDeviceInfo *device_info = Pa_GetDeviceInfo(device);
    if (device_info == NULL)
    {
        Pa_Terminate();
        return error_type_message(csErrorPortAudio, "Unable to get device info");
    }
    log_info("Audio device: %s", device_info->name);
    PaStreamParameters params = {
        .device = device,
        .channelCount = (int)count,
        .sampleFormat = paInt16,
        .suggestedLatency = device_info->defaultLowOutputLatency,
        .hostApiSpecificStreamInfo = NULL,
    };
    player->sampler = sampler_create(sample_rate, count, channels);
    if (player->sampler == NULL)
    {
        Pa_Terminate();
        return error_type_message(csErrorInit, "Unable to create sampler");
    }
    log_info("Sampler created: %d funcs, %d gens, %d handlers", func_list_size(), sampler_gen_count(player->sampler), event_list_size());
    player->stream = NULL;
    pa_error = Pa_OpenStream(&player->stream, NULL, &params, (int)sample_rate, paFramesPerBufferUnspecified, paNoFlag, player_callback, player->sampler);
    if (pa_error != paNoError)
    {
        sampler_free(player->sampler);
        Pa_Terminate();
        return error_type_message(csErrorPortAudio, "Unable to open stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    const PaStreamInfo *stream_info = Pa_GetStreamInfo(player->stream);
    if (pa_error != paNoError)
    {
        sampler_free(player->sampler);
        Pa_CloseStream(player->stream);
        Pa_Terminate();
        return error_type_message(csErrorPortAudio, "Unable to get stream info: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    log_info("Stream opened: %.1f ms, %.3f kHz", stream_info->outputLatency * 1e3, stream_info->sampleRate * 1e-3);
    pa_error = Pa_StartStream(player->stream);
    if (pa_error != paNoError)
    {
        sampler_free(player->sampler);
        Pa_CloseStream(player->stream);
        Pa_Terminate();
        return error_type_message(csErrorPortAudio, "Unable to start stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    return csErrorNone;
}

csError player_close(Player *player)
{
    PaError pa_error = Pa_CloseStream(player->stream);
    if (pa_error != paNoError)
    {
        sampler_free(player->sampler);
        Pa_Terminate();
        return error_type_message(csErrorPortAudio, "Unable to close stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    sampler_free(player->sampler);
    pa_error = Pa_Terminate();
    if (pa_error != paNoError)
    {
        return error_type_message(csErrorPortAudio, "Unable to terminate: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    return csErrorNone;
}

#endif // CSYNTH_PLAYER_H
