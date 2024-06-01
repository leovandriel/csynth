//
// record.h - Record key presses
//
#ifndef CSYNTH_RECORD_H
#define CSYNTH_RECORD_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/key_event.h"
#include "../../mem/key_list.h"

typedef struct
{
    KeyList *list;
    const char *filename;
    double time;
    void *handle;
} RecordContext;

static double record_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    context->time += delta;
    return gen_eval(args[0]);
}

int record_listen(EventType type, void *event_, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    if (type == EventTypeKey)
    {
        KeyEvent *event = (KeyEvent *)event_;
        if (event->key != ' ')
        {
            TimedKeyEvent timed_event = {
                .key = event->key,
                .time = context->time,
            };
            key_list_add(context->list, timed_event);
        }
    }
    return 0;
}

void record_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    context->handle = event_add_listener(record_listen, context);
    context->list = key_list_alloc();
}

static void record_free(void *context_)
{
    RecordContext *context = (RecordContext *)context_;
    event_remove_listener(context->handle);
    key_list_write_filename(context->list, context->filename);
    key_list_free(context->list);
}

Func *record(Func *func, const char *filename)
{
    RecordContext initial = (RecordContext){
        .filename = filename,
    };
    return func_create(record_init, record_eval, record_free, sizeof(RecordContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
}

#endif // CSYNTH_RECORD_H
