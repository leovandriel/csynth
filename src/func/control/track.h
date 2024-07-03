//
// track.h - Track and save key presses
//
#ifndef CSYNTH_TRACK_H
#define CSYNTH_TRACK_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../mem/key_list.h"

typedef struct
{
    KeyList list;
    const char *filename;
    const void *handler;
} TrackContext;

static double track_eval(__U int count, Gen **args, Eval *eval, __U void *context_)
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
            TimedKeyboardEvent timed_event = {
                .key = event->key.keyboard,
                .time = event->time,
            };
            csError error = key_list_add(&context->list, timed_event);
            error_catch(error);
        }
    }
}

static int track_init(__U int count, __U Gen **args, void *context_)
{
    TrackContext *context = (TrackContext *)context_;
    const void *handler = event_add_handler(track_handle_event, context);
    if (handler == NULL)
    {
        return error_catch_message(csErrorInit, "Unable to add track handler");
    }
    context->handler = handler;
    context->list = NULL;
    return 0;
}

static void track_free(__U int count, void *context_)
{
    TrackContext *context = (TrackContext *)context_;
    csError error = event_remove_handler(context->handler);
    error_catch(error);
    error = key_list_write_filename(&context->list, context->filename);
    error_catch(error);
    key_list_clear(&context->list);
}

Func *track_create(const char *filename, Func *input)
{
    TrackContext initial = {.filename = filename};
    return func_create(track_init, track_eval, track_free, sizeof(TrackContext), &initial, FuncFlagNone, FUNCS(input));
}

#endif // CSYNTH_TRACK_H
