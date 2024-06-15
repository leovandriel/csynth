//
// track.h - Track and save key presses
//
#ifndef CSYNTH_TRACK_H
#define CSYNTH_TRACK_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/keyboard_event.h"
#include "../../mem/key_list.h"
#include "../../util/config.h"

typedef struct
{
    KeyList *list;
    const char *filename;
    void *handle;
} TrackContext;

static double track_eval(__attribute__((unused)) int count, Gen **args, __attribute__((unused)) double delta, __attribute__((unused)) void *context_)
{
    // TODO(leo): consider converting to non-func
    return gen_eval(args[0]);
}

int track_listen(EventType type, void *event_, void *context_)
{
    TrackContext *context = (TrackContext *)context_;
    if (type == EventTypeKeyboard)
    {
        KeyboardEvent *event = (KeyboardEvent *)event_;
        TimedKeyboardEvent timed_event = {
            .key = event->key,
            .time = event->time,
        };
        key_list_add(context->list, timed_event);
    }
    return 0;
}

void track_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    TrackContext *context = (TrackContext *)context_;
    context->handle = event_add_listener(track_listen, context);
    context->list = key_list_alloc();
}

static void track_free(__attribute__((unused)) int count, void *context_)
{
    TrackContext *context = (TrackContext *)context_;
    event_remove_listener(context->handle);
    key_list_write_filename(context->list, context->filename);
    key_list_free(context->list);
}

Func *track(Func *func, const char *filename)
{
    TrackContext initial = (TrackContext){
        .filename = filename,
    };
    return func_create(track_init, track_eval, track_free, sizeof(TrackContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
}

Func *track_(Func *func)
{
    return track(func, CONFIG_DEFAULT_REC_FILENAME);
}

#endif // CSYNTH_TRACK_H
