//
// midi_event.h - Func lifecyle for MIDI events
//
#ifndef CSYNTH_MIDI_EVENT_H
#define CSYNTH_MIDI_EVENT_H

#include "../core/gen.h"
#include "./event.h"

typedef enum
{
    MidiTypeNoteOff = 0x8,
    MidiTypeNoteOn = 0x9,
    MidiTypePolyphonic = 0xA,
    MidiTypeControlChange = 0xB,
    MidiTypeProgramChange = 0xC,
    MidiTypeChannelPressure = 0xD,
    MidiTypePitchBend = 0xE,
    MidiTypeSystem = 0xF,
} MidiType;

typedef int (*midi_event_listener)(double time, MidiType type, uint32_t channel, uint32_t data1, uint32_t data2, void *context);

typedef struct
{
    double time;
    MidiType type;
    uint32_t channel;
    uint32_t data1;
    uint32_t data2;
} MidiEvent;

typedef struct
{
    void *handle;
    midi_event_listener midi_listener;
} MidiEventContext;

int midi_event_broadcast(double time, MidiType type, uint32_t channel, uint32_t data1, uint32_t data2)
{
    MidiEvent event = {
        .time = time,
        .type = type,
        .channel = channel,
        .data1 = data1,
        .data2 = data2,
    };
    return event_broadcast(EventTypeMidi, &event);
}

int midi_event_listen(EventType type, void *event_, void *context_)
{
    MidiEventContext *context = (MidiEventContext *)context_;
    if (type == EventTypeMidi)
    {
        MidiEvent *event = (MidiEvent *)event_;
        return context->midi_listener(event->time, event->type, event->channel, event->data1, event->data2, context);
    }
    return 0;
}

void midi_event_add(MidiEventContext *context)
{
    context->handle = event_add_listener(midi_event_listen, context);
}

void midi_event_remove(MidiEventContext *context)
{
    event_remove_listener(context->handle);
    context->handle = NULL;
}

void midi_event_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context)
{
    midi_event_add((MidiEventContext *)context);
}

void midi_event_free(__attribute__((unused)) int count, void *context)
{
    midi_event_remove((MidiEventContext *)context);
}

#endif // CSYNTH_MIDI_EVENT_H