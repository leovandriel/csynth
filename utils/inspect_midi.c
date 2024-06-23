//usr/bin/gcc "$0" -o bin/inspect_midi -Wall -Wextra -O3 -lportmidi && ./bin/inspect_midi "$@"; exit $?

#include <portmidi.h>
#include <porttime.h>
#include <stdio.h>

#include "../src/util/error.h"

#define MIDI_EVENT_BUFFER_SIZE 1024

const char *message_type(uint8_t type)
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
    printf("[PortMIDI]\n");
    PmError pm_error = Pm_Initialize();
    if (pm_error != pmNoError)
    {
        return error_catch_message(csErrorPortMidi, "Unable to initialize: %s (%d)", Pm_GetErrorText(pm_error), pm_error);
    }
    printf("Devices\n");
    int device_count = Pm_CountDevices();
    if (device_count == 0)
    {
        return error_catch_message(csErrorMidi, "No MIDI devices found");
    }
    int device_input_default = Pm_GetDefaultInputDeviceID();
    int device_output_default = Pm_GetDefaultOutputDeviceID();
    for (int i = 0; i < device_count; i++)
    {
        const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
        printf("  %d:%s%s\n", i, i == device_input_default ? " (default input)" : "", i == device_output_default ? " (default output)" : "");
        printf("    interface: %s\n", info->interf);
        printf("    name: %s\n", info->name);
        printf("    input: %s\n", info->input ? "yes" : "no");
        printf("    output: %s\n", info->output ? "yes" : "no");
        printf("    opened: %s\n", info->opened ? "yes" : "no");
        printf("    isVirtual: %s\n", info->is_virtual ? "yes" : "no");
    }
    PortMidiStream *stream = NULL;
    pm_error = Pm_OpenInput(&stream, device_input_default, NULL, MIDI_EVENT_BUFFER_SIZE, NULL, NULL);
    if (pm_error != pmNoError)
    {
        return error_catch_message(csErrorPortMidi, "Unable to open input: %s (%d)", Pm_GetErrorText(pm_error), pm_error);
    }
    printf("Use MIDI device to log events. Ctrl+C to exit\n");
    PmEvent buffer[MIDI_EVENT_BUFFER_SIZE];
    for (;;)
    {
        int count = Pm_Read(stream, buffer, 1024);
        if (count < 0)
        {
            pm_error = count;
            return error_catch_message(csErrorPortMidi, "Unable to read stream: %s (%d)", Pm_GetErrorText(pm_error), pm_error);
        }
        for (int i = 0; i < count; i++)
        {
            PmEvent event = buffer[i];
            PmTimestamp time = event.timestamp;
            uint8_t status = Pm_MessageStatus(event.message);
            uint8_t type = status >> 4;
            uint8_t channel = (status & 0x0F) + 1;
            uint8_t data1 = Pm_MessageData1(event.message);
            uint8_t data2 = Pm_MessageData2(event.message);
            printf("time: %d  type: %d (%s)  channel: %d  data1: %d  data2: %d\n", time, type, message_type(type), channel, data1, data2);
        }
        Pt_Sleep(1);
    }
    pm_error = Pm_Close(stream);
    if (pm_error != pmNoError)
    {
        return error_catch_message(csErrorPortMidi, "Unable to close: %s (%d)", Pm_GetErrorText(pm_error), pm_error);
        return pm_error;
    }
    pm_error = Pm_Terminate();
    if (pm_error != pmNoError)
    {
        return error_catch_message(csErrorPortMidi, "Unable to terminate: %s (%d)", Pm_GetErrorText(pm_error), pm_error);
    }

    return 0;
}
