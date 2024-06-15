//
// midi.h - Handle key input from MIDI device
//
#ifndef CSYNTH_MIDI_H
#define CSYNTH_MIDI_H

#include <portmidi.h>
#include <porttime.h>

#include "../event/midi_event.h"
#include "./terminal.h"

#define MIDI_EVENT_BUFFER_SIZE 64

typedef struct
{
    PortMidiStream *stream;
} MidiContext;

int midi_initialize(MidiContext *context)
{
    PmError err = Pm_Initialize();
    if (err != pmNoError)
    {
        fprintf(stderr, "initialize error: %s\n", Pm_GetErrorText(err));
        return err;
    }
    int count = Pm_CountDevices();
    if (count == 0)
    {
        fprintf(stderr, "no midi devices found\n");
        return -1;
    }
    PmDeviceID input = Pm_GetDefaultInputDeviceID();
    if (input < 0)
    {
        fprintf(stderr, "no default midi devices\n");
        return -1;
    }
    err = Pm_OpenInput(&context->stream, input, NULL, MIDI_EVENT_BUFFER_SIZE, NULL, NULL);
    if (err != pmNoError)
    {
        fprintf(stderr, "open error: %s\n", Pm_GetErrorText(err));
        return err;
    }
    const PmDeviceInfo *info = Pm_GetDeviceInfo(input);
    printf("MIDI initialized: %s on %s\n", info->name, info->interf);
    return 0;
}

int midi_broadcast(MidiContext *context)
{
    PmEvent buffer[MIDI_EVENT_BUFFER_SIZE];
    int count = Pm_Read(context->stream, buffer, 1024);
    if (count < 0)
    {
        PmError err = count;
        fprintf(stderr, "read error: %s\n", Pm_GetErrorText(err));
        return err;
    }
    for (int i = 0; i < count; i++)
    {
        double time = (double)buffer[i].timestamp / 1000.;
        uint32_t status = Pm_MessageStatus(buffer[i].message);
        MidiType type = status >> 4;
        uint32_t channel = status & 0x0F;
        uint32_t data1 = Pm_MessageData1(buffer[i].message);
        uint32_t data2 = Pm_MessageData2(buffer[i].message);
        int err = midi_event_broadcast(time, type, channel, data1, data2);
        if (err)
        {
            return err;
        }
    }
    return 0;
}

int midi_terminate(MidiContext *context)
{
    PmError err = Pm_Close(context->stream);
    if (err != pmNoError)
    {
        fprintf(stderr, "close error: %s\n", Pm_GetErrorText(err));
        return err;
    }
    err = Pm_Terminate();
    if (err != pmNoError)
    {
        fprintf(stderr, "terminate error: %s\n", Pm_GetErrorText(err));
        return err;
    }
    return 0;
}

int midi_loop(__attribute__((unused)) double duration, int exit_key)
{
    MidiContext context = {0};
    int err = midi_initialize(&context);
    if (err)
    {
        return err;
    }
    struct termios term = terminal_setup(0);
    signal(SIGINT, terminal_handler);
    while (!terminal_signaled())
    {
        int key = terminal_read(exit_key);
        if (key > 0)
        {
            keyboard_event_broadcast(time_wall(), key);
        }
        else if (key < 0)
        {
            break;
        }
        Pt_Sleep(1);
        err = midi_broadcast(&context);
        if (err)
        {
            break;
        }
    }
    terminal_restore(term);
    err = midi_terminate(&context);
    if (err)
    {
        return err;
    }
    return 0;
}

#endif // CSYNTH_MIDI_H
