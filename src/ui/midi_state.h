#ifndef CSYNTH_MIDI_STATE_H
#define CSYNTH_MIDI_STATE_H

#include "../event/control_event.h"

#define MIDI_CHANNEL_COUNT 16
#define MIDI_NOTE_COUNT 128

/**
 * @brief Full state of a MIDI device, used as a cache by function evaluation.
 */
typedef struct
{
    /** @brief NoteOn state for each note on each channel. */
    uint8_t noteOn[MIDI_CHANNEL_COUNT * MIDI_NOTE_COUNT];
    /** @brief Polyphonic pressure state for each note on each channel. */
    uint8_t polyphonicPressure[MIDI_CHANNEL_COUNT * MIDI_NOTE_COUNT];
    /** @brief Controller state for each controller on each channel. */
    uint8_t controller[MIDI_CHANNEL_COUNT * MIDI_NOTE_COUNT];
    /** @brief Program change state for each channel. */
    uint8_t programChange[MIDI_CHANNEL_COUNT];
    /** @brief Channel pressure state for each channel. */
    uint8_t channelPressure[MIDI_CHANNEL_COUNT];
    /** @brief Pitch bend state for each channel. */
    uint16_t pitchBend[MIDI_CHANNEL_COUNT];
} MidiState;

static MidiState midi_state_global = {0};

/**
 * @brief Get the MIDI state for a given type, channel, and data1.
 *
 * @param type The type of MIDI event.
 * @param channel The MIDI channel.
 * @param data1 The first data byte.
 * @return The MIDI state as a double.
 */
double midi_state_get(MidiType type, uint8_t channel, uint8_t data1)
{
    switch (type)
    {
    case MidiTypeNoteOff:
        break;
    case MidiTypeNoteOn:
        return (double)midi_state_global.noteOn[channel * MIDI_NOTE_COUNT + data1] / 127.0;
    case MidiTypePolyphonicPressure:
        return (double)midi_state_global.polyphonicPressure[channel * MIDI_NOTE_COUNT + data1] / 127.0;
    case MidiTypeController:
        return (double)midi_state_global.controller[channel * MIDI_NOTE_COUNT + data1] / 127.0;
    case MidiTypeProgramChange:
        return (double)midi_state_global.programChange[channel] / 127.0;
    case MidiTypeChannelPressure:
        return (double)midi_state_global.channelPressure[channel] / 127.0;
    case MidiTypePitchBend:
        return (double)midi_state_global.pitchBend[channel] / 16383.0;
    case MidiTypeSystem:
        break;
    }
    return 0.0;
}

void midi_state_set(MidiType type, uint8_t channel, uint8_t data1, uint8_t data2)
{
    switch (type)
    {
    case MidiTypeNoteOff:
        midi_state_global.noteOn[channel * MIDI_NOTE_COUNT + data1] = 0;
        break;
    case MidiTypeNoteOn:
        midi_state_global.noteOn[channel * MIDI_NOTE_COUNT + data1] = data2;
        break;
    case MidiTypePolyphonicPressure:
        midi_state_global.polyphonicPressure[channel * MIDI_NOTE_COUNT + data1] = data2;
        break;
    case MidiTypeController:
        midi_state_global.controller[channel * MIDI_NOTE_COUNT + data1] = data2;
        break;
    case MidiTypeProgramChange:
        midi_state_global.programChange[channel] = data1;
        break;
    case MidiTypeChannelPressure:
        midi_state_global.channelPressure[channel] = data1;
        break;
    case MidiTypePitchBend:
        midi_state_global.pitchBend[channel] = (data2 << 7) | data1;
        break;
    case MidiTypeSystem:
        break;
    }
}

#endif // CSYNTH_MIDI_STATE_H
