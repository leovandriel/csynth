#ifndef CSYNTH_MEM_H
#define CSYNTH_MEM_H

#include <stdio.h>

#include "../../core/func.h"
#include "../../core/gen.h"
#include "../../event/state_event.h"
#include "../../util/error.h"

/** @see mem_create */
typedef struct
{
    /** @brief Time since last broadcast. */
    double time;
} MemContext;

static double mem_eval(__U size_t count, Gen **args, Eval *eval, __U void *context_)
{
#ifdef ALLOC_TRACE
    MemContext *context = (MemContext *)context_;
    if (context->time >= 1.0 && eval != NULL)
    {
        AllocStat stat = alloc_stat();
        state_event_broadcast(eval->wall_time, StateEventKeyTypeLabel, "alloc", StateEventValueTypeSize, &stat.alloc_size);
        state_event_broadcast(eval->wall_time, StateEventKeyTypeLabel, "free", StateEventValueTypeSize, &stat.free_size);
        context->time = 0;
    }
    context->time += eval->wall_tick;
#endif
    return gen_eval(args[0], eval);
}

/**
 * @brief Create a function that displays memory usage.
 *
 * @param input Input signal.
 * @return Func* Memory debug function.
 */
Func *mem_create(Func *input)
{
    MemContext initial = {
        .time = 1.0,
    };
    return func_create(NULL, mem_eval, NULL, sizeof(MemContext), &initial, FuncFlagNone, input);
}

#endif // CSYNTH_MEM_H
