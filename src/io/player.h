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

typedef void (*player_event_loop)(double duration, int exit_key);

typedef struct
{
    player_event_loop loop;
    double duration;
    int sample_rate;
    int exit_key;
} PlayerConfig;

void player_event_loop_no_terminal(double duration, __U int exit_key)
{
    if (duration <= 0)
    {
        duration = FLT_MAX;
    }
    Pa_Sleep((long)(duration * 1000));
}

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

csError player_play_channels_no_cleanup(int count, Func **channels, PlayerConfig config)
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
    fprintf(stdout, "\r\e[KAudio device: %s\n", device_info->name);
    PaStreamParameters params = {
        .device = device,
        .channelCount = count,
        .sampleFormat = paInt16,
        .suggestedLatency = device_info->defaultLowOutputLatency,
        .hostApiSpecificStreamInfo = NULL,
    };
    csError error = display_show();
    if (error != csErrorNone)
    {
        Pa_Terminate();
        return error;
    }
    Sampler *sampler = sampler_create(count, channels, config.sample_rate);
    if (sampler == NULL)
    {
        Pa_Terminate();
        return error_type_message(csErrorInit, "Unable to create sampler");
    }
    PaStream *stream = NULL;
    pa_error = Pa_OpenStream(&stream, NULL, &params, config.sample_rate, paFramesPerBufferUnspecified, paNoFlag, player_callback, sampler);
    if (pa_error != paNoError)
    {
        sampler_free(sampler);
        Pa_Terminate();
        return error_type_message(csErrorPortAudio, "Unable to open stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    const PaStreamInfo *stream_info = Pa_GetStreamInfo(stream);
    if (pa_error != paNoError)
    {
        sampler_free(sampler);
        Pa_CloseStream(stream);
        Pa_Terminate();
        return error_type_message(csErrorPortAudio, "Unable to get stream info: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    fprintf(stdout, "\r\e[KStream opened: %.1f ms, %.3f kHz\n", stream_info->outputLatency * 1000, stream_info->sampleRate / 1000);
    pa_error = Pa_StartStream(stream);
    if (pa_error != paNoError)
    {
        sampler_free(sampler);
        Pa_CloseStream(stream);
        Pa_Terminate();
        return error_type_message(csErrorPortAudio, "Unable to start stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    config.loop(config.duration, config.exit_key);
    pa_error = Pa_CloseStream(stream);
    if (pa_error != paNoError)
    {
        sampler_free(sampler);
        Pa_Terminate();
        return error_type_message(csErrorPortAudio, "Unable to close stream: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    sampler_free(sampler);
    error = display_hide();
    if (error != csErrorNone)
    {
        Pa_Terminate();
        return error;
    }
    pa_error = Pa_Terminate();
    if (pa_error != paNoError)
    {
        return error_type_message(csErrorPortAudio, "Unable to terminate: %s", Pa_GetErrorText(pa_error), pa_error);
    }
    return csErrorNone;
}

csError player_play_with_cleanup(int count, Func **channels, PlayerConfig config)
{
    csError error = player_play_channels_no_cleanup(count, channels, config);
    cleanup_all();
    return error;
}

const PlayerConfig player_config_terminal = {.loop = terminal_loop, .duration = 0, .sample_rate = DEFAULT_SAMPLE_RATE, .exit_key = DEFAULT_EXIT_KEY};
const PlayerConfig player_config_no_terminal = {.loop = player_event_loop_no_terminal, .duration = 0, .sample_rate = DEFAULT_SAMPLE_RATE, .exit_key = DEFAULT_EXIT_KEY};

int play(Func *root) { return player_play_with_cleanup(1, (Func *[]){root}, player_config_terminal); }
int play_stereo(Func *left, Func *right) { return player_play_with_cleanup(2, (Func *[]){left, right}, player_config_terminal); }

int play_duration(Func *root, double duration)
{
    PlayerConfig config = player_config_no_terminal;
    config.duration = duration;
    return player_play_with_cleanup(1, (Func *[]){root}, config);
}

int play_(Func *root, double duration) { return play_duration(root, duration); }

int play_stereo_duration(Func *left, Func *right, double duration)
{
    PlayerConfig config = player_config_no_terminal;
    config.duration = duration;
    return player_play_with_cleanup(2, (Func *[]){left, right}, config);
}

#endif // CSYNTH_PLAYER_H
