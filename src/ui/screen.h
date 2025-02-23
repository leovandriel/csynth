#ifndef CSYNTH_SCREEN_H
#define CSYNTH_SCREEN_H

#include <SDL2/SDL.h>

#include "../event/control_event.h"
#include "../util/time.h"

#define SCREEN_FPS 120

typedef struct
{
    uint32_t *buffer;
    size_t pitch;
    pthread_mutex_t mutex;
} ScreenContext;

int screen_lock(uint32_t **buffer, size_t *pitch, void *context_)
{
    ScreenContext *context = (ScreenContext *)context_;
    *pitch = context->pitch;
    *buffer = context->buffer;
    pthread_mutex_lock(&context->mutex);
    return 0;
}

void screen_unlock(void *context_)
{
    ScreenContext *context = (ScreenContext *)context_;
    pthread_mutex_unlock(&context->mutex);
}

int screen_loop(double duration, int exit_key, RenderPipe *pipe)
{
#ifdef AUTO_EXIT
    duration = AUTO_EXIT * 1e-3;
#endif
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("csynth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pipe->width, pipe->height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, pipe->width, pipe->height);
    ScreenContext context = {
        .buffer = (uint32_t *)malloc_(pipe->width * pipe->height * sizeof(uint32_t)),
        .pitch = pipe->width * sizeof(uint32_t),
    };
    pthread_mutex_init(&context.mutex, NULL);
    render_pipe_set(pipe, screen_lock, screen_unlock, &context);
    SDL_Event event = {0};
    int running = 1;
    double start = time_sec();

    for (double time = time_sec(); running && (duration == 0.0 || time < start + duration); time = time_sec())
    {
        void *lockedPixels;
        int pitch;
        if (SDL_LockTexture(texture, NULL, &lockedPixels, &pitch) == 0)
        {
            memcpy(lockedPixels, context.buffer, pipe->height * pitch);
            SDL_UnlockTexture(texture);
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
            {
                SDL_Keysym key = event.key.keysym;
                if (key.sym == exit_key || (key.mod & KMOD_CTRL && key.sym == SDLK_c))
                {
                    running = 0;
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
    }

    render_pipe_unset(pipe);
    pthread_mutex_destroy(&context.mutex);
    free_(context.buffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

#endif // CSYNTH_SCREEN_H
