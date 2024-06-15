//usr/bin/gcc "$0" -o bin/inspect_audio -Wall -Wextra -O3 -lportaudio && ./bin/inspect_audio "$@"; exit $?

#include <portaudio.h>
#include <stdio.h>

#define PA_ERR_CHECK(_err)                                                \
    if ((_err) < 0)                                                       \
    {                                                                     \
        fprintf(stderr, "Error: %s (%d)\n", Pa_GetErrorText(_err), _err); \
        return _err;                                                      \
    }                                                                     \
    (void)0

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

int main()
{
    printf("[PortAudio]\n");
    printf("Version\n");
    const PaVersionInfo *version_info = Pa_GetVersionInfo();
    printf("  versionText: %s\n", version_info->versionText);
    PaError err = Pa_Initialize();
    PA_ERR_CHECK(err);

    printf("HostApis\n");
    PaHostApiIndex host_count = Pa_GetHostApiCount();
    if (host_count == 0)
    {
        fprintf(stderr, "No audio hosts found.\n");
        return 0;
    }
    PA_ERR_CHECK(host_count);
    PaHostApiIndex host_default = Pa_GetDefaultHostApi();
    for (int i = 0; i < host_count; i++)
    {
        const PaHostApiInfo *info = Pa_GetHostApiInfo(i);
        printf("  %d:%s\n", i, i == host_default ? " (default)" : "");
        printf("    structVersion: %d\n", info->structVersion);
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
        fprintf(stderr, "No audio devices found.\n");
        return 0;
    }
    PA_ERR_CHECK(device_count);
    PaDeviceIndex device_input_default = Pa_GetDefaultInputDevice();
    PaDeviceIndex device_output_default = Pa_GetDefaultOutputDevice();
    for (int i = 0; i < device_count; i++)
    {
        const PaDeviceInfo *info = Pa_GetDeviceInfo(i);
        printf("  %d:%s%s\n", i, i == device_input_default ? " (default input)" : "", i == device_output_default ? " (default output)" : "");
        printf("    structVersion: %d\n", info->structVersion);
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

    err = Pa_Terminate();
    PA_ERR_CHECK(err);
    return 0;
}
