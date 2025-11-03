#ifndef CSYNTH_SCREEN_RUN_H
#define CSYNTH_SCREEN_RUN_H

#include "../ui/screen.h"
#include "./player_run.h"
#include "./run.h"

typedef struct
{
    ScreenContext *context;
} ScreenRun;

csError screen_run_init(void *context)
{
    ScreenRun *run = (ScreenRun *)context;
    if (run == NULL)
    {
        return error_type_message(csErrorMemoryAlloc, "Unable to allocate memory for screen run");
    }
    return screen_init(run->context);
}

csError screen_run_tick(void *context)
{
    ScreenRun *run = (ScreenRun *)context;
    return screen_tick(run->context);
}

void screen_run_free(void *context)
{
    ScreenRun *run = (ScreenRun *)context;
    screen_free(run->context);
    free_(run->context);
    free_(run);
}

RunLoop screen_run(RenderPipe *pipe)
{
    ScreenRun *run = (ScreenRun *)malloc_(sizeof(ScreenRun));
    if (run != NULL)
    {
        run->context = (ScreenContext *)malloc_(sizeof(ScreenContext));
        run->context->pipe = pipe;
    }
    return (RunLoop){
        .init = screen_run_init,
        .tick = screen_run_tick,
        .free = screen_run_free,
        .context = run,
    };
}

int play_screen(Func *input, RenderPipe *pipe) { return run_loop(player_run(input), screen_run(pipe)); }
int play_screen_stereo(Func *left, Func *right, RenderPipe *pipe) { return run_loop(player_run(left, right), screen_run(pipe)); }

#endif // CSYNTH_SCREEN_RUN_H
