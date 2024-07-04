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
#include "../util/logger.h"
#include "./sampler.h"

#define EXIT_KEY '\e' // ESC key

typedef void (*player_event_loop)(double duration, int exit_key);

typedef struct
{
    player_event_loop loop;
    double duration;
    size_t sample_rate;
    int exit_key;
} PlayerConfig;

void player_event_loop_no_terminal(double duration, __U int exit_key)
{
    if (duration <= 0.0)
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

csError player_play_channels_no_cleanup(PlayerConfig config, size_t count, Func **channels)
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
    csError error = display_show();
    if (error != csErrorNone)
    {
        Pa_Terminate();
        return error;
    }
    Sampler *sampler = sampler_create(config.sample_rate, count, channels);
    if (sampler == NULL)
    {
        Pa_Terminate();
        return error_type_message(csErrorInit, "Unable to create sampler");
    }
    log_info("Sampler created: %d funcs, %d gens, %d handlers", func_list_size(), sampler_gen_count(sampler), event_list_size());
    PaStream *stream = NULL;
    pa_error = Pa_OpenStream(&stream, NULL, &params, (int)config.sample_rate, paFramesPerBufferUnspecified, paNoFlag, player_callback, sampler);
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
    log_info("Stream opened: %.1f ms, %.3f kHz", stream_info->outputLatency * 1000, stream_info->sampleRate / 1000);
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

csError player_play_with_cleanup(PlayerConfig config, size_t count, Func **channels)
{
    csError error = player_play_channels_no_cleanup(config, count, channels);
    cleanup_all();
    return error;
}

const PlayerConfig PLAYER_CONFIG_TERMINAL = {
    .loop = terminal_loop,
    .duration = 0.0,
    .sample_rate = SAMPLE_RATE,
    .exit_key = EXIT_KEY,
};
const PlayerConfig PLAYER_CONFIG_NO_TERMINAL = {
    .loop = player_event_loop_no_terminal,
    .duration = 0.0,
    .sample_rate = SAMPLE_RATE,
    .exit_key = EXIT_KEY,
};

int play_channels(size_t count, Func **channels) { return player_play_with_cleanup(PLAYER_CONFIG_TERMINAL, count, channels); } /* player_ */
int play(Func *input) { return play_channels(FUNCS(input)); }                                                                  /* player_ */
int play_stereo(Func *left, Func *right) { return play_channels(FUNCS(left, right)); }                                         /* player_ */

int play_channels_duration(double duration, size_t count, Func **channels) /* player_ */
{
    PlayerConfig config = PLAYER_CONFIG_NO_TERMINAL;
    config.duration = duration;
    return player_play_with_cleanup(config, count, channels);
}
int play_duration(double duration, Func *input) { return play_channels_duration(duration, FUNCS(input)); }                          /* player_ */
int play_stereo_duration(double duration, Func *left, Func *right) { return play_channels_duration(duration, FUNCS(left, right)); } /* player_ */

#endif // CSYNTH_PLAYER_H
