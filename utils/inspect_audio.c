//usr/bin/gcc "$0" -o bin/inspect_audio -Wall -Wextra -O3 -lportaudio && ./bin/inspect_audio "$@"; exit $?

#include <portaudio.h>
#include <stdio.h>

#include "../src/util/error.h"

const char *host_type_string(PaHostApiTypeId type)
{
    switch (type)
    {
    case paInDevelopment:
        return "InDevelopment";
    case paDirectSound:
        return "DirectSound";
    case paMME:
        return "MME";
    case paASIO:
        return "ASIO";
    case paSoundManager:
        return "SoundManager";
    case paCoreAudio:
        return "CoreAudio";
    case paOSS:
        return "OSS";
    case paALSA:
        return "ALSA";
    case paAL:
        return "AL";
    case paBeOS:
        return "BeOS";
    case paWDMKS:
        return "WDMKS";
    case paJACK:
        return "JACK";
    case paWASAPI:
        return "WASAPI";
    case paAudioScienceHPI:
        return "AudioScienceHPI";
    }
    return "unknown";
}

int main(void)
{
    printf("[PortAudio]\n");
    printf("Version\n");
    const PaVersionInfo *version_info = Pa_GetVersionInfo();
    printf("  versionText: %s\n", version_info->versionText);
    PaError pa_error = Pa_Initialize();
    if (pa_error != paNoError)
    {
        return error_type_message(csErrorPortAudio, "Unable to initialize: %s (%d)", Pa_GetErrorText(pa_error), pa_error);
    }
    printf("HostApis\n");
    PaHostApiIndex host_count = Pa_GetHostApiCount();
    if (host_count == 0)
    {
        return error_type_message(csErrorAudio, "No audio hosts found");
    }
    if (host_count < 0)
    {
        pa_error = host_count;
        return error_type_message(csErrorPortAudio, "Unable to get hosts: %s (%d)", Pa_GetErrorText(pa_error), pa_error);
    }
    PaHostApiIndex host_default = Pa_GetDefaultHostApi();
    for (int i = 0; i < host_count; i++)
    {
        const PaHostApiInfo *info = Pa_GetHostApiInfo(i);
        printf("  %d:%s\n", i, i == host_default ? " (default)" : "");
        printf("    type: %d (%s)\n", info->type, host_type_string(info->type));
        printf("    name: %s\n", info->name);
        printf("    deviceCount: %d\n", info->deviceCount);
        printf("    defaultInputDevice: %d (%s)\n", info->defaultInputDevice, Pa_GetDeviceInfo(info->defaultInputDevice)->name);
        printf("    defaultOutputDevice: %d (%s)\n", info->defaultOutputDevice, Pa_GetDeviceInfo(info->defaultOutputDevice)->name);
    }

    printf("Devices\n");
    PaDeviceIndex device_count = Pa_GetDeviceCount();
    if (device_count == 0)
    {
        return error_type_message(csErrorAudio, "No devices found");
        return 0;
    }
    if (device_count < 0)
    {
        pa_error = device_count;
        return error_type_message(csErrorPortAudio, "Unable to get devices: %s (%d)", Pa_GetErrorText(pa_error), pa_error);
    }
    PaDeviceIndex device_input_default = Pa_GetDefaultInputDevice();
    PaDeviceIndex device_output_default = Pa_GetDefaultOutputDevice();
    for (int i = 0; i < device_count; i++)
    {
        const PaDeviceInfo *info = Pa_GetDeviceInfo(i);
        printf("  %d:%s%s\n", i, i == device_input_default ? " (default input)" : "", i == device_output_default ? " (default output)" : "");
        printf("    name: %s\n", info->name);
        printf("    hostApi: %d (%s)\n", info->hostApi, Pa_GetHostApiInfo(info->hostApi)->name);
        printf("    maxInputChannels: %d\n", info->maxInputChannels);
        printf("    maxOutputChannels: %d\n", info->maxOutputChannels);
        printf("    defaultLowInputLatency: %f s\n", info->defaultLowInputLatency);
        printf("    defaultLowOutputLatency: %f s\n", info->defaultLowOutputLatency);
        printf("    defaultHighInputLatency: %f s\n", info->defaultHighInputLatency);
        printf("    defaultHighOutputLatency: %f s\n", info->defaultHighOutputLatency);
        printf("    defaultSampleRate: %.1f Hz\n", info->defaultSampleRate);
    }

    pa_error = Pa_Terminate();
    if (pa_error != paNoError)
    {
        return error_type_message(csErrorPortAudio, "Unable to terminate: %s (%d)", Pa_GetErrorText(pa_error), pa_error);
    }
    return 0;
}
