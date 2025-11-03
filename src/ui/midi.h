#ifndef CSYNTH_MIDI_H
#define CSYNTH_MIDI_H

#include <portmidi.h>
#include <porttime.h>

#include "../event/control_event.h"
#include "../util/logger.h"
#include "./midi_state.h"

#define MIDI_EVENT_BUFFER_SIZE 1024
#define MIDI_CHANNEL_COUNT 16
#define MIDI_NOTE_COUNT 128

/** @see midi_create */
typedef struct
{
    /** @brief PortMidi message stream. */
    PortMidiStream *stream;
} MidiContext;

csError midi_initialize(MidiContext *context)
{
    PmError pm_error = Pm_Initialize();
    if (pm_error != pmNoError)
    {
        return error_type_message(csErrorPortMidi, "Unable to initialize: %s", Pm_GetErrorText(pm_error));
    }
    int count = Pm_CountDevices();
    if (count == 0)
    {
        Pm_Terminate();
        return error_type_message(csErrorMidi, "No MIDI devices found");
    }
    PmDeviceID input = Pm_GetDefaultInputDeviceID();
    if (input < 0)
    {
        Pm_Terminate();
        return error_type_message(csErrorMidi, "No default MIDI device found");
    }
    const PmDeviceInfo *info = Pm_GetDeviceInfo(input);
    if (info == NULL)
    {
        Pm_Terminate();
        return error_type_message(csErrorMidi, "Unable to get MIDI device info");
    }
    pm_error = Pm_OpenInput(&context->stream, input, NULL, MIDI_EVENT_BUFFER_SIZE, NULL, NULL);
    if (pm_error != pmNoError)
    {
        Pm_Terminate();
        return error_type_message(csErrorPortMidi, "Unable to terminate: %s", Pm_GetErrorText(pm_error));
    }
    log_info("MIDI initialized: %s, %s", info->name, info->interf);
    return csErrorNone;
}

csError midi_read_broadcast(MidiContext *context)
{
    PmEvent buffer[MIDI_EVENT_BUFFER_SIZE];
    int count = Pm_Read(context->stream, buffer, 1024);
    if (count < 0)
    {
        PmError pm_error = count;
        if (pm_error == pmBufferOverflow)
        {
            log_error("MIDI buffer overflow, events were lost");
            return csErrorNone;
        }
        return error_type_message(csErrorPortMidi, "Unable to read: %s", Pm_GetErrorText(pm_error));
    }
    for (int i = 0; i < count; i++)
    {
        double time = (double)buffer[i].timestamp * 1e-3;
        uint8_t status = Pm_MessageStatus(buffer[i].message);
        MidiType type = status >> 4;
        uint8_t channel = status & 0x0F;
        uint8_t data1 = Pm_MessageData1(buffer[i].message);
        uint8_t data2 = Pm_MessageData2(buffer[i].message);
        control_event_broadcast_midi(time, type, channel, data1, data2);
        midi_state_set(type, channel, data1, data2);
    }
    return csErrorNone;
}

csError midi_terminate(MidiContext *context)
{
    PmError pm_error = Pm_Close(context->stream);
    if (pm_error != pmNoError)
    {
        return error_type_message(csErrorPortMidi, "Unable to close: %s", Pm_GetErrorText(pm_error));
    }
    pm_error = Pm_Terminate();
    if (pm_error != pmNoError)
    {
        return error_type_message(csErrorPortMidi, "Unable to terminate: %s", Pm_GetErrorText(pm_error));
    }
    return csErrorNone;
}

double midi_time(void)
{
    return (double)Pt_Time() * 1e-3;
}

#endif // CSYNTH_MIDI_H
