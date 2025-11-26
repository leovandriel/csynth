#ifndef CSYNTH_SCREEN_H
#define CSYNTH_SCREEN_H

#include <SDL2/SDL.h>

#include "../event/control_event.h"
#include "../util/time.h"
#include "./render_pipe.h"

#define SCREEN_FPS 120
#define EXIT_KEY '\e' // ESC key

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;
    uint32_t *buffer;
    size_t pitch;
    pthread_mutex_t mutex;
    RenderPipe *pipe;
    double start;
} ScreenContext;

bool screen_lock(uint32_t **buffer, size_t *pitch, void *context_)
{
    ScreenContext *context = (ScreenContext *)context_;
    *pitch = context->pitch;
    *buffer = context->buffer;
    pthread_mutex_lock(&context->mutex);
    return false;
}

void screen_unlock(void *context_)
{
    ScreenContext *context = (ScreenContext *)context_;
    pthread_mutex_unlock(&context->mutex);
}

csError screen_init(ScreenContext *context)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return csErrorDisplay;
    }
    context->buffer = (uint32_t *)malloc_(context->pipe->width * context->pipe->height * sizeof(uint32_t)),
    context->pitch = context->pipe->width * sizeof(uint32_t),
    context->window = SDL_CreateWindow("csynth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, context->pipe->width, context->pipe->height, SDL_WINDOW_SHOWN);
    context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED);
    context->texture = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, context->pipe->width, context->pipe->height);
    pthread_mutex_init(&context->mutex, NULL);
    render_pipe_set(context->pipe, screen_lock, screen_unlock, context);
    context->start = time_sec();
    return csErrorNone;
}

csError screen_tick(ScreenContext *context)
{
    double time = time_sec();

    void *lockedPixels;
    int pitch;
    if (SDL_LockTexture(context->texture, NULL, &lockedPixels, &pitch) == 0)
    {
        memcpy(lockedPixels, context->buffer, context->pipe->height * pitch);
        SDL_UnlockTexture(context->texture);
    }
    SDL_RenderClear(context->renderer);
    SDL_RenderCopy(context->renderer, context->texture, NULL, NULL);
    SDL_RenderPresent(context->renderer);

    SDL_Event event = {0};
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return -1;
        case SDL_KEYDOWN:
        {
            SDL_Keysym key = event.key.keysym;
            if (key.sym == EXIT_KEY || (key.mod & KMOD_CTRL && key.sym == SDLK_c))
            {
                return -1;
            }
            else
            {
                control_event_broadcast_keyboard(time, key.sym);
            }
            break;
        }
        }
    }

    double delta = time_sec() - time;
    if (delta < 1.0 / SCREEN_FPS)
    {
        time_sleep(1.0 / SCREEN_FPS - delta);
    }
    return csErrorNone;
}

void screen_free(ScreenContext *context)
{
    render_pipe_unset(context->pipe);
    pthread_mutex_destroy(&context->mutex);
    free_(context->buffer);
    SDL_DestroyTexture(context->texture);
    SDL_DestroyRenderer(context->renderer);
    SDL_DestroyWindow(context->window);
    SDL_Quit();
}

#endif // CSYNTH_SCREEN_H
