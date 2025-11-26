#ifndef CSYNTH_RENDER_PIPE_H
#define CSYNTH_RENDER_PIPE_H

#include <stddef.h>

typedef bool (*render_lock)(uint32_t **buffer, size_t *pitch, void *context);
typedef void (*render_unlock)(void *context);

typedef struct
{
    size_t width;
    size_t height;
    render_lock lock;
    render_unlock unlock;
    void *context;
} RenderPipe;

bool render_pipe_lock(RenderPipe *pipe, void *buffer, size_t *pitch)
{
    if (pipe->lock != NULL)
    {
        return pipe->lock(buffer, pitch, pipe->context);
    }
    return true;
}

void render_pipe_unlock(RenderPipe *pipe)
{
    if (pipe->unlock != NULL)
    {
        pipe->unlock(pipe->context);
    }
}

void render_pipe_set(RenderPipe *pipe, render_lock lock, render_unlock unlock, void *context)
{
    pipe->lock = lock;
    pipe->unlock = unlock;
    pipe->context = context;
}

void render_pipe_unset(RenderPipe *pipe)
{
    pipe->lock = NULL;
    pipe->unlock = NULL;
    pipe->context = NULL;
}

#endif // CSYNTH_RENDER_PIPE_H
