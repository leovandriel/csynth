#ifndef CSYNTH_CONTROL_EVENT_H
#define CSYNTH_CONTROL_EVENT_H

#include "../core/gen.h"
#include "./event.h"
#include <stdbool.h>

#define KEYBOARD_EVENT_UP 1792833
#define KEYBOARD_EVENT_DOWN 1792834

typedef enum
{
    MidiTypeNoteOff = 0x8,
    MidiTypeNoteOn = 0x9,
    MidiTypePolyphonicPressure = 0xA,
    MidiTypeController = 0xB,
    MidiTypeProgramChange = 0xC,
    MidiTypeChannelPressure = 0xD,
    MidiTypePitchBend = 0xE,
    MidiTypeSystem = 0xF,
} MidiType;

/**
 * @brief A MIDI message.
 */
typedef struct
{
    /** @brief Type of MIDI event. */
    MidiType type;
    /** @brief Channel of the event. */
    uint8_t channel;
    /** @brief Data byte 1. */
    uint8_t data1;
    /** @brief Data byte 2. */
    uint8_t data2;
} MidiKey;

typedef enum
{
    ControlEventTypeNone = 0,
    ControlEventTypeKeyboard,
    ControlEventTypeMidi,
} ControlEventType;

/**
 * @brief Key of a control event.
 */
typedef struct
{
    /** @brief Type of the key. */
    ControlEventType type;
    union
    {
        /** @brief If keyboard, the key index. */
        int keyboard;
        /** @brief If MIDI, the MIDI key. */
        MidiKey midi;
    };
} ControlEventKey;

/**
 * @brief Event from a control source, like a pad or knob.
 */
typedef struct
{
    /** @brief Time of the event, seconds since start. */
    double time;
    /** @brief Key of the event, e.g. keyboard or MIDI. */
    ControlEventKey key;
} ControlEvent;

typedef void (*control_handle_event)(ControlEvent *event, void *context);

/**
 * @brief Context for handling control events.
 */
typedef struct
{
    /** @brief Handle to the event listener. */
    const void *handler;
    /** @brief Handle event callback. */
    control_handle_event handle_event;
} ControlEventContext;

bool control_event_midi_equal(MidiKey key_a, MidiKey key_b)
{
    switch (key_a.type)
    {
    case MidiTypeNoteOff:
    case MidiTypeNoteOn:
        return (key_b.type == MidiTypeNoteOn || key_b.type == MidiTypeNoteOff) && key_a.channel == key_b.channel && key_a.data1 == key_b.data1;
    case MidiTypePolyphonicPressure:
    case MidiTypeController:
    case MidiTypeProgramChange:
        return key_a.type == key_b.type && key_a.channel == key_b.channel && key_a.data1 == key_b.data1;
    case MidiTypeChannelPressure:
    case MidiTypePitchBend:
        return key_a.type == key_b.type && key_a.channel == key_b.channel;
    case MidiTypeSystem:
        break;
    }
    return false;
}

bool control_event_key_equal(ControlEventKey key_a, ControlEventKey key_b)
{
    if (key_a.type != key_b.type)
    {
        return false;
    }
    switch (key_a.type)
    {
    case ControlEventTypeNone:
        break;
    case ControlEventTypeKeyboard:
        return key_a.keyboard == key_b.keyboard;
    case ControlEventTypeMidi:
        return control_event_midi_equal(key_a.midi, key_b.midi);
    }
    return false;
}

void control_event_broadcast_keyboard(double time, int key)
{
    ControlEvent event = {
        .time = time,
        .key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        },
    };
    event_broadcast(EventTypeControl, &event);
}

void control_event_broadcast_midi(double time, MidiType type, uint8_t channel, uint8_t data1, uint8_t data2)
{
    ControlEvent event = {
        .time = time,
        .key = {
            .type = ControlEventTypeMidi,
            .midi = {
                .type = type,
                .channel = channel,
                .data1 = data1,
                .data2 = data2,
            },
        },
    };
    event_broadcast(EventTypeControl, &event);
}

void control_event_handle_event(EventType type, const void *event_, void *context_)
{
    ControlEventContext *context = (ControlEventContext *)context_;
    if (type == EventTypeControl)
    {
        ControlEvent *event = (ControlEvent *)event_;
        context->handle_event(event, context);
    }
}

csError control_event_add(ControlEventContext *context)
{
    const void *handler = event_add_handler(control_event_handle_event, context);
    if (handler == NULL)
    {
        return error_type_message(csErrorInit, "Unable to add control event handler");
    }
    context->handler = handler;
    return csErrorNone;
}

csError control_event_remove(ControlEventContext *context)
{
    csError error = event_remove_handler(context->handler);
    if (error != csErrorNone)
    {
        return error;
    }
    context->handler = NULL;
    return csErrorNone;
}

csError control_event_init(__U size_t count, __U Gen **args, void *context)
{
    return control_event_add((ControlEventContext *)context);
}

void control_event_free(__U size_t count, void *context)
{
    csError error = control_event_remove((ControlEventContext *)context);
    error_catch(error);
}

#endif // CSYNTH_CONTROL_EVENT_H
