//usr/bin/gcc "$0" -o bin/inspect_midi -Wall -Wextra -O3 -lportmidi && ./bin/inspect_midi "$@"; exit $?

#include <portmidi.h>
#include <porttime.h>
#include <stdio.h>

#define PA_ERR_CHECK(_err)                                                \
    if ((_err) < 0)                                                       \
    {                                                                     \
        fprintf(stderr, "Error: %s (%d)\n", Pm_GetErrorText(_err), _err); \
        return _err;                                                      \
    }                                                                     \
    (void)0

#define BUFFER_SIZE 1024

const char *message_type(uint32_t type)
{
    switch (type)
    {
    case 0x8:
        return "NoteOff";
    case 0x9:
        return "NoteOn";
    case 0xA:
        return "PolyphonicKeyPressure";
    case 0xB:
        return "ControlChange";
    case 0xC:
        return "ProgramChange";
    case 0xD:
        return "ChannelPressure";
    case 0xE:
        return "PitchBendChange";
    case 0xF:
        return "System";
    default:
        return "unknown";
    }
}

int main()
{
    printf("[PortMidi]\n");
    PmError err = Pm_Initialize();
    PA_ERR_CHECK(err);
    printf("Devices\n");
    int device_count = Pm_CountDevices();
    if (device_count == 0)
    {
        fprintf(stderr, "No MIDI devices found.\n");
        return 0;
    }
    int device_input_default = Pm_GetDefaultInputDeviceID();
    int device_output_default = Pm_GetDefaultOutputDeviceID();
    for (int i = 0; i < device_count; i++)
    {
        const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
        printf("  %d:%s%s\n", i, i == device_input_default ? " (default input)" : "", i == device_output_default ? " (default output)" : "");
        printf("    structVersion: %d\n", info->structVersion);
        printf("    interface: %s\n", info->interf);
        printf("    name: %s\n", info->name);
        printf("    input: %s\n", info->input ? "yes" : "no");
        printf("    output: %s\n", info->output ? "yes" : "no");
        printf("    opened: %s\n", info->opened ? "yes" : "no");
        printf("    isVirtual: %s\n", info->is_virtual ? "yes" : "no");
    }
    PortMidiStream *stream = NULL;
    err = Pm_OpenInput(&stream, device_input_default, NULL, BUFFER_SIZE, NULL, NULL);
    PA_ERR_CHECK(err);
    printf("Use MIDI device to log events. Ctrl+C to exit\n");
    PmEvent buffer[BUFFER_SIZE];
    for (;;)
    {
        int count = Pm_Read(stream, buffer, 1024);
        PA_ERR_CHECK(count);
        for (int i = 0; i < count; i++)
        {
            PmEvent event = buffer[i];
            PmTimestamp time = event.timestamp;
            uint32_t status = Pm_MessageStatus(event.message);
            uint32_t type = status >> 4;
            uint32_t channel = status & 0x0F;
            uint32_t data1 = Pm_MessageData1(event.message);
            uint32_t data2 = Pm_MessageData2(event.message);
            printf("time: %d  type: %d (%s)  channel: %d  data1: %d  data2: %d\n", time, type, message_type(type), channel, data1, data2);
        }
        Pt_Sleep(1);
    }
    err = Pm_Close(stream);
    PA_ERR_CHECK(err);
    err = Pm_Terminate();
    PA_ERR_CHECK(err);
    return 0;
}
