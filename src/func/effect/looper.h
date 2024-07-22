//
// looper.h - Loop samples
//
#ifndef CSYNTH_LOOPER_H
#define CSYNTH_LOOPER_H

#include <stdlib.h>
#include <string.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"
#include "../../mem/buffer.h"

typedef struct
{
    ControlEventContext parent;
    ControlEventKey key;
    Buffer buffer;
    size_t index;
    bool recording;
    bool reset;
} LooperContext;

static double looper_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    LooperContext *context = (LooperContext *)context_;
    double tick = gen_eval(args[0], eval);
    if (eval == NULL || eval->compute_flag)
    {
        size_t size = (size_t)(1.0 / tick);
        context->index = buffer_resize(&context->buffer, size, context->index);
    }
    double *samples = context->buffer.samples;
    double output = 0.0;
    if (samples != NULL)
    {
        if (context->recording)
        {
            if (context->reset)
            {
                gen_reset(args[1]);
                buffer_fill(&context->buffer);
                context->reset = false;
            }
            output = gen_eval(args[1], eval);
            samples[context->index] = output;
        }
        else
        {
            output = samples[context->index];
        }
        context->index = (context->index + 1) % context->buffer.size;
    }
    return output;
}

static void looper_handle_event(ControlEvent *event, void *context_)
{
    LooperContext *context = (LooperContext *)context_;
    if (control_event_key_equal(event->key, context->key) && (event->key.type != ControlEventTypeMidi || event->key.midi.data2 != 0))
    {
        context->recording = !context->recording;
        if (context->recording)
        {
            context->reset = true;
        }
        state_event_broadcast(event->time, StateEventKeyTypeControl, &context->key, StateEventValueTypeBoolInv, &context->recording);
    }
}

static bool looper_init(__U size_t count, __U Gen **args, void *context_)
{
    LooperContext *context = (LooperContext *)context_;
    state_event_broadcast(0, StateEventKeyTypeControl, &context->key, StateEventValueTypeBoolInv, &context->recording);
    csError error = control_event_add(&context->parent);
    return error_catch(error);
}

static void looper_free(__U size_t count, void *context_)
{
    LooperContext *context = (LooperContext *)context_;
    buffer_free(&context->buffer);
}

Func *looper_keyboard_create(int key, Func *tick, Func *input)
{
    LooperContext initial = {
        .parent = {.handle_event = looper_handle_event},
        .key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        },
    };
    return func_create(looper_init, looper_eval, looper_free, sizeof(LooperContext), &initial, FuncFlagNone, tick, input);
}

Func *looper_midi_create(int channel, int control, Func *tick, Func *input)
{
    LooperContext initial = {
        .parent = {.handle_event = looper_handle_event},
        .key = {
            .type = ControlEventTypeMidi,
            .midi = {
                .type = MidiTypeController,
                .channel = channel - 1,
                .data1 = control,
            },
        },
    };
    return func_create(looper_init, looper_eval, looper_free, sizeof(LooperContext), &initial, FuncFlagNone, tick, input);
}

#endif // CSYNTH_LOOPER_H
