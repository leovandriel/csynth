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

typedef void (*midi_handle_event)(double time, MidiType type, uint8_t channel, uint8_t data1, uint8_t data2, void *context);

typedef struct
{
    double time;
    MidiType type;
    uint8_t channel;
    uint8_t data1;
    uint8_t data2;
} MidiEvent;

typedef struct
{
    uint8_t channel;
    uint8_t control;
} MidiKey;

typedef struct
{
    const void *handler;
    midi_handle_event handle_event;
} MidiEventContext;

void midi_event_broadcast(double time, MidiType type, uint8_t channel, uint8_t data1, uint8_t data2)
{
    MidiEvent event = {
        .time = time,
        .type = type,
        .channel = channel,
        .data1 = data1,
        .data2 = data2,
    };
    event_broadcast(EventTypeMidi, &event);
}

void midi_handle_event_(EventType type, const void *event_, void *context_)
{
    MidiEventContext *context = (MidiEventContext *)context_;
    if (type == EventTypeMidi)
    {
        MidiEvent *event = (MidiEvent *)event_;
        context->handle_event(event->time, event->type, event->channel, event->data1, event->data2, context);
    }
}

csError midi_event_add(MidiEventContext *context)
{
    const void *handler = event_add_handler(midi_handle_event_, context);
    if (handler == NULL)
    {
        return error_type_message(csErrorInit, "Unable to add MIDI event handler");
    }
    context->handler = handler;
    return csErrorNone;
}

csError midi_event_remove(MidiEventContext *context)
{
    csError error = event_remove_handler(context->handler);
    if (error != csErrorNone)
    {
        return error;
    }
    context->handler = NULL;
    return csErrorNone;
}

int midi_event_init(__U int count, __U Gen **args, __U double delta, void *context)
{
    csError error = midi_event_add((MidiEventContext *)context);
    return error_catch(error);
}

void midi_event_free(__U int count, void *context)
{
    csError error = midi_event_remove((MidiEventContext *)context);
    error_catch(error);
}

#endif // CSYNTH_MIDI_EVENT_H
