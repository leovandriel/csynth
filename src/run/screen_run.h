#ifndef CSYNTH_SCREEN_RUN_H
#define CSYNTH_SCREEN_RUN_H

#include "../ui/screen.h"
#include "./player_run.h"
#include "./run.h"

csError screen_run_init(void *context)
{
    return screen_init((ScreenContext *)context);
}

csRunOrError screen_run_tick(void *context)
{
    return (csRunOrError)screen_tick((ScreenContext *)context);
}

void screen_run_free(void *context)
{
    screen_free((ScreenContext *)context);
}

RunLoop screen_run(RenderPipe *pipe)
{
    ScreenContext *context = (ScreenContext *)malloc_(sizeof(ScreenContext));
    if (context != NULL)
    {
        context->pipe = pipe;
    }
    return (RunLoop){
        .init = screen_run_init,
        .tick = screen_run_tick,
        .free = screen_run_free,
        .context = context,
        .manage_context = true,
    };
}

int play_screen(Func *input, RenderPipe *pipe) { return run_loop(player_run(input), screen_run(pipe)); }
int play_screen_stereo(Func *left, Func *right, RenderPipe *pipe) { return run_loop(player_run(left, right), screen_run(pipe)); }

#endif // CSYNTH_SCREEN_RUN_H
