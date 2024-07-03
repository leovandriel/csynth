//
// midi_keyboard.h - MIDI keyboard controls
//
#ifndef CSYNTH_MIDI_KEYBOARD_H
#define CSYNTH_MIDI_KEYBOARD_H

#include <math.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"

typedef struct
{
    int number;
    double velocity;
    double factor;
    int reset;
} MidiKeyboardKey;

typedef struct
{
    ControlEventContext parent;
    uint8_t channel;
    int count;
    int capacity;
    MidiKeyboardKey *keys;
    int semitones;
} MidiKeyboardContext;

static double midi_keyboard_eval(__U int count, __U Gen **args, Eval *eval, void *context_)
{
    MidiKeyboardContext *context = (MidiKeyboardContext *)context_;
    double output = 0.;
    for (int i = 0; i < context->count; i++)
    {
        MidiKeyboardKey *key = &context->keys[i];
        if (key->reset != 0)
        {
            gen_reset(args[i]);
            key->reset = 0;
        }
        double restore = eval->tick[EvalTickPitch];
        eval->tick[EvalTickPitch] = restore * key->factor;
        output += gen_eval(args[i], eval) * key->velocity;
        eval->tick[EvalTickPitch] = restore;
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
            int index = context->count < context->capacity ? context->count++ : context->count - 1;
            context->keys[index] = (MidiKeyboardKey){
                .number = event->key.midi.data1,
                .velocity = (double)event->key.midi.data2 / 64.0,
                .factor = exp2((double)event->key.midi.data1 / (double)context->semitones),
                .reset = 1,
            };
        }
        else if (event->key.midi.type == MidiTypeNoteOff)
        {
            uint8_t number = event->key.midi.data1;
            for (int i = 0; i < context->count; i++)
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

static int midi_keyboard_init(__U int count, __U Gen **args, void *context_)
{
    MidiKeyboardContext *context = (MidiKeyboardContext *)context_;
    MidiKeyboardKey *keys = (MidiKeyboardKey *)malloc_(context->capacity * sizeof(MidiKeyboardKey));
    if (keys == NULL)
    {
        return error_catch(csErrorMemoryAlloc);
    }
    context->keys = keys;
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

void midi_keyboard_free(__U int count, void *context_)
{
    MidiKeyboardContext *context = (MidiKeyboardContext *)context_;
    free_(context->keys);
    csError error = control_event_remove((ControlEventContext *)context);
    error_catch(error);
}

Func *midi_keyboard_create(int channel, int semitones, int count, Func **inputs)
{
    MidiKeyboardContext initial = {
        .parent = {.handle_event = midi_keyboard_handle_event},
        .channel = channel - 1,
        .capacity = count,
        .semitones = semitones,
    };
    return func_create(midi_keyboard_init, midi_keyboard_eval, midi_keyboard_free, sizeof(MidiKeyboardContext), &initial, FuncFlagNone, count, inputs);
}

Func *midi_keyboard_count(int channel, int semitones, int count, Func *input)
{
    Func **inputs = (Func **)malloc_(count * sizeof(Func *));
    if (inputs == NULL)
    {
        return error_null(csErrorMemoryAlloc);
    }
    for (int i = 0; i < count; i++)
    {
        inputs[i] = input;
    }
    Func *output = midi_keyboard_create(channel, semitones, count, inputs);
    free_(inputs);
    return output;
}

#endif // CSYNTH_MIDI_KEYBOARD_H
