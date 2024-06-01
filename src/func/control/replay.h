//
// replay.h - Replay key presses
//
#ifndef CSYNTH_REPLAY_H
#define CSYNTH_REPLAY_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/key_event.h"
#include "../../util/key_list.h"

typedef struct
{
    KeyList *list;
    const char *filename;
    size_t index;
    double time;
} ReplayContext;

static double replay_eval(__attribute__((unused)) int count, Gen **args, double delta, void *context_)
{
    ReplayContext *context = (ReplayContext *)context_;
    size_t size = key_list_len(context->list);
    while (context->index < size)
    {
        TimedKeyEvent event = key_list_get(context->list, context->index);
        if (event.time > context->time)
        {
            break;
        }
        if (event.key != ' ')
        {
            key_event_broadcast(event.key);
        }
        context->index++;
    }
    context->time += delta;
    return gen_eval(args[0]);
}

void replay_init(__attribute__((unused)) int count, __attribute__((unused)) Gen **args, __attribute__((unused)) double delta, void *context_)
{
    ReplayContext *context = (ReplayContext *)context_;
    context->list = key_list_alloc();
    key_list_read_filename(context->list, context->filename);
}

static void replay_free(void *context_)
{
    ReplayContext *context = (ReplayContext *)context_;
    key_list_free(context->list);
}

Func *replay(Func *func, const char *filename)
{
    ReplayContext initial = (ReplayContext){
        .filename = filename,
    };
    return func_create(replay_init, replay_eval, replay_free, sizeof(ReplayContext), &initial, FUNC_FLAG_DEFAULT, 1, func);
}

#endif // CSYNTH_REPLAY_H
