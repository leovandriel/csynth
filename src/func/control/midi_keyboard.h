#ifndef CSYNTH_MIDI_KEYBOARD_H
#define CSYNTH_MIDI_KEYBOARD_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"

/**
 * @brief A key on a MIDI keyboard.
 */
typedef struct
{
    /** @brief MIDI key number. */
    uint8_t number;
    /** @brief Velocity of the key press. */
    double velocity;
    /** @brief Gain multiplier. */
    double factor;
    /** @brief Whether to reset the input. */
    bool reset;
} MidiKeyboardKey;

/** @see midi_keyboard_create */
typedef struct
{
    /** @brief Super struct, allowing use of control_event_free. */
    ControlEventContext parent;
    /** @brief MIDI channel to listen to. */
    uint8_t channel;
    /** @brief Number of keys active. */
    size_t count;
    /** @brief Maximum number of keys active. */
    size_t capacity;
    /** @brief Array of active keys. */
    MidiKeyboardKey *keys;
    /** @brief Number of semitones in an octave. */
    size_t semitones;
} MidiKeyboardContext;

static double midi_keyboard_eval(__U size_t count, __U Gen **args, Eval *eval, void *context_)
{
    MidiKeyboardContext *context = (MidiKeyboardContext *)context_;
    double output = 0.;
    for (size_t i = 0; i < context->count; i++)
    {
        MidiKeyboardKey *key = &context->keys[i];
        if (key->reset)
        {
            gen_reset(args[i]);
            key->reset = false;
        }
        if (eval != NULL)
        {
            double restore = eval->params[EvalParamPitchTick];
            eval->params[EvalParamPitchTick] = restore * key->factor;
            output += gen_eval(args[i], eval) * key->velocity;
            eval->params[EvalParamPitchTick] = restore;
        }
        else
        {
            output += gen_eval(args[i], eval) * key->velocity;
        }
    }
    return output;
}

static void midi_keyboard_handle_event(ControlEvent *event, void *context_)
{
    MidiKeyboardContext *context = (MidiKeyboardContext *)context_;
    if (event->key.type == ControlEventTypeMidi && event->key.midi.channel == context->channel)
    {
        if (event->key.midi.type == MidiTypeNoteOn)
        {
            size_t index = context->count < context->capacity ? context->count++ : context->count - 1;
            context->keys[index] = (MidiKeyboardKey){
                .number = event->key.midi.data1,
                .velocity = (double)event->key.midi.data2 / 64.0,
                .factor = exp2((double)event->key.midi.data1 / (double)context->semitones),
                .reset = true,
            };
        }
        else if (event->key.midi.type == MidiTypeNoteOff)
        {
            uint8_t number = event->key.midi.data1;
            for (size_t i = 0; i < context->count; i++)
            {
                if (context->keys[i].number == number)
                {
                    context->keys[i] = context->keys[--context->count];
                    break;
                }
            }
        }
    }
}

static csError midi_keyboard_init(__U size_t count, __U Gen **args, void *context_)
{
    MidiKeyboardContext *context = (MidiKeyboardContext *)context_;
    MidiKeyboardKey *keys = (MidiKeyboardKey *)malloc_(context->capacity * sizeof(MidiKeyboardKey));
    if (keys == NULL)
    {
        return error_type(csErrorMemoryAlloc);
    }
    context->keys = keys;
    return control_event_add(&context->parent);
}

void midi_keyboard_free(__U size_t count, void *context_)
{
    MidiKeyboardContext *context = (MidiKeyboardContext *)context_;
    free_(context->keys);
    csError error = control_event_remove((ControlEventContext *)context);
    error_catch(error);
}

/**
 * @brief A keyboard control function that maps a MIDI key to a pitch of a
 * single function.
 *
 * @param channel MIDI channel to listen to.
 * @param semitones Number of semitones in an octave.
 * @param count Maximum number of keys active.
 * @param inputs Input functions, usual identical.
 * @return Func*
 */
Func *midi_keyboard_create(int channel, size_t semitones, size_t count, Func **inputs)
{
    MidiKeyboardContext initial = {
        .parent = {.handle_event = midi_keyboard_handle_event},
        .channel = channel - 1,
        .capacity = count,
        .semitones = semitones,
    };
    return func_create_args(midi_keyboard_init, midi_keyboard_eval, midi_keyboard_free, NULL, sizeof(MidiKeyboardContext), &initial, FuncFlagNone, count, inputs, "input");
}

/**
 * @brief A keyboard control function that maps a MIDI key to a pitch of a
 * single function.
 *
 * @param channel MIDI channel to listen to.
 * @param semitones Number of semitones in an octave.
 * @param count Maximum number of keys active.
 * @param input Input function, usual identical.
 * @return Func*
 */
Func *midi_keyboard_count(int channel, size_t semitones, size_t count, Func *input)
{
    Func **inputs = (Func **)malloc_(count * sizeof(Func *));
    if (inputs == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    for (size_t i = 0; i < count; i++)
    {
        inputs[i] = input;
    }
    Func *output = midi_keyboard_create(channel, semitones, count, inputs);
    free_(inputs);
    return output;
}

#endif // CSYNTH_MIDI_KEYBOARD_H
