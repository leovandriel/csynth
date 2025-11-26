#ifndef CSYNTH_LOOPER_H
#define CSYNTH_LOOPER_H

#include <stdlib.h>
#include <string.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../event/state_event.h"
#include "../../mem/buffer.h"

/** @see looper_create */
typedef struct
{
    /** @brief Super struct, allowing use of control_event_free. */
    ControlEventContext parent;
    /** @brief Key to start/stop recording. */
    ControlEventKey key;
    /** @brief Buffer to store samples. */
    Buffer buffer;
    /** @brief Index of the current sample. */
    size_t index;
    /** @brief Flag to indicate if recording. */
    bool recording;
    /** @brief Flag to indicate function reset. */
    bool reset;
} LooperContext;

static double looper_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    LooperContext *context = (LooperContext *)context_;
    double tick = gen_eval(args[0], eval);
    if (eval == NULL || eval->compute_flag)
    {
        size_t size = (size_t)(1.0 / tick);
        buffer_resize(&context->buffer, size, &context->index);
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
        if (++context->index >= context->buffer.size)
        {
            context->index = 0;
        }
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

static csError looper_init(__U size_t count, __U Gen **args, void *context_)
{
    LooperContext *context = (LooperContext *)context_;
    state_event_broadcast(0, StateEventKeyTypeControl, &context->key, StateEventValueTypeBoolInv, &context->recording);
    return control_event_add(&context->parent);
}

static void looper_free(__U size_t count, void *context_)
{
    LooperContext *context = (LooperContext *)context_;
    buffer_free(&context->buffer);
}

/**
 * @brief Create function to interactively record and loop samples, using key
 * stroke.
 *
 * @param key Input key to start/stop recording.
 * @param tick Periods per sample
 * @param input Input signal to record.
 * @return Func* Looper function.
 */
Func *looper_keyboard_create(int key, Func *tick, Func *input)
{
    LooperContext initial = {
        .parent = {.handle_event = looper_handle_event},
        .key = {
            .type = ControlEventTypeKeyboard,
            .keyboard = key,
        },
    };
    return func_create(looper_init, looper_eval, looper_free, NULL, sizeof(LooperContext), &initial, FuncFlagNone, tick, input);
}

/**
 * @brief Create function to interactively record and loop samples, using MIDI
 * controller.
 *
 * @param channel MIDI channel to listen to.
 * @param control MIDI controller to listen to.
 * @param tick Periods per sample
 * @param input Input signal to record.
 * @return Func* Looper function.
 */
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
    return func_create(looper_init, looper_eval, looper_free, NULL, sizeof(LooperContext), &initial, FuncFlagNone, tick, input);
}

#endif // CSYNTH_LOOPER_H
