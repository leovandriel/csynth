#ifndef CSYNTH_REPLAY_H
#define CSYNTH_REPLAY_H

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/control_event.h"
#include "../../mem/key_list.h"

/** @see replay_create */
typedef struct
{
    /** @brief Linked list of keyboard events. */
    KeyList list;
    /** @brief Current event, awaiting to be broadcasted. */
    KeyboardEvent *current;
    /** @brief Filename of the replay file. */
    const char *filename;
    /** @brief Current time of the replay. */
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

static int replay_init(__U size_t count, __U Gen **args, void *context_)
{
    ReplayContext *context = (ReplayContext *)context_;
    csError error = key_list_read_filename(&context->list, context->filename);
    if (error != csErrorNone)
    {
        return error;
    }
    context->current = context->list;
    return csErrorNone;
}

static void replay_free(__U size_t count, void *context_)
{
    ReplayContext *context = (ReplayContext *)context_;
    key_list_clear(&context->list);
}

/**
 * @brief Create a function that replays a keyboard event file, emulating key
 * presses.
 *
 * @param filename Filename of the replay file.
 * @param tick Function to determine the time between key presses.
 * @param input Input function to trigger.
 * @return Func* Replay function.
 */
Func *replay_create(const char *filename, Func *tick, Func *input)
{
    ReplayContext initial = {.filename = filename};
    return func_create(replay_init, replay_eval, replay_free, sizeof(ReplayContext), &initial, FuncFlagNone, tick, input);
}

#endif // CSYNTH_REPLAY_H
