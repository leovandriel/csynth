#ifndef CSYNTH_TRACK_H
#define CSYNTH_TRACK_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../mem/key_list.h"

/** @see track_create */
typedef struct
{
    /** @brief Linked list of keyboard events. */
    KeyList list;
    /** @brief Filename of the track file. */
    const char *filename;
    /** @brief Handle to the event listener. */
    const void *handler;
} TrackContext;

static double track_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
    // TODO(leo): consider converting to non-func
    return gen_eval(args[0], eval);
}

static void track_handle_event(EventType type, const void *event_, void *context_)
{
    TrackContext *context = (TrackContext *)context_;
    if (type == EventTypeControl)
    {
        ControlEvent *event = (ControlEvent *)event_;
        if (event->key.type == ControlEventTypeKeyboard)
        {
            KeyboardEvent keyboard_event = {
                .key = event->key.keyboard,
                .time = event->time,
            };
            csError error = key_list_add(&context->list, keyboard_event);
            error_catch(error);
        }
    }
}

static int track_init(__U size_t count, __U Gen **args, void *context_)
{
    TrackContext *context = (TrackContext *)context_;
    const void *handler = event_add_handler(track_handle_event, context);
    if (handler == NULL)
    {
        return error_type_message(csErrorInit, "Unable to add track handler");
    }
    context->handler = handler;
    return csErrorNone;
}

static void track_free(__U size_t count, void *context_)
{
    TrackContext *context = (TrackContext *)context_;
    csError error = event_remove_handler(context->handler);
    error_catch(error);
    error = key_list_write_filename(&context->list, context->filename);
    error_catch(error);
    key_list_clear(&context->list);
}

/**
 * @brief Create a function that records keyboard events to a file.
 *
 * This file can be used to replay the events at a later time, using the replay
 * function.
 *
 * @param filename Filename of the track file.
 * @param input Input function, simply forwarded to output.
 * @return Func* Track function.
 */
Func *track_create(const char *filename, Func *input)
{
    TrackContext initial = {.filename = filename};
    return func_create(track_init, track_eval, track_free, sizeof(TrackContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_TRACK_H
