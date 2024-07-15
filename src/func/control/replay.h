//
// replay.h - Replay key presses
//
#ifndef CSYNTH_REPLAY_H
#define CSYNTH_REPLAY_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../mem/key_list.h"

typedef struct
{
    KeyList list;
    TimedKeyboardEvent *current;
    const char *filename;
    size_t index;
    double time;
} ReplayContext;

static double replay_eval(__U size_t count, Gen **args, Eval *eval, void *context_)
{
    ReplayContext *context = (ReplayContext *)context_;
    while (context->current && context->current->time <= context->time)
    {
        control_event_broadcast_keyboard(context->current->time, context->current->key);
        context->current = context->current->next;
    }
    double tick = gen_eval(args[0], eval);
    double input = gen_eval(args[1], eval);
    context->time += tick;
    return input;
}

static bool replay_init(__U size_t count, __U Gen **args, void *context_)
{
    ReplayContext *context = (ReplayContext *)context_;
    csError error = key_list_read_filename(&context->list, context->filename);
    if (error != csErrorNone)
    {
        return error_catch(error);
    }
    context->current = context->list;
    return 0;
}

static void replay_free(__U size_t count, void *context_)
{
    ReplayContext *context = (ReplayContext *)context_;
    key_list_clear(&context->list);
}

Func *replay_create(const char *filename, Func *tick, Func *input)
{
    ReplayContext initial = {.filename = filename};
    return func_create(replay_init, replay_eval, replay_free, sizeof(ReplayContext), &initial, FuncFlagNone, ARGS(tick, input));
}

#endif // CSYNTH_REPLAY_H
