#ifndef CSYNTH_PLAYER_RUN_H
#define CSYNTH_PLAYER_RUN_H

#include "../io/player.h"
#include "./run.h"

typedef struct
{
    Player player;
    size_t sample_rate;
    size_t count;
    Func **channels;
} PlayerRun;

csError player_run_init(__U void *context)
{
    PlayerRun *run = (PlayerRun *)context;
    if (run == NULL)
    {
        return error_type_message(csErrorMemoryAlloc, "Unable to allocate memory for player run");
    }
    return player_open(&run->player, run->sample_rate, run->count, run->channels);
}

void player_run_free(void *context)
{
    PlayerRun *run = (PlayerRun *)context;
    player_close(&run->player);
    free_(run);
}

RunLoop player_run_channels(size_t count, Func **channels)
{
    PlayerRun *run = (PlayerRun *)malloc_(sizeof(PlayerRun));
    if (run != NULL)
    {
        run->sample_rate = SAMPLE_RATE;
        run->count = count;
        run->channels = channels;
    }
    return (RunLoop){
        .init = player_run_init,
        .free = player_run_free,
        .context = run,
    };
}

#define player_run(...) player_run_channels(ARGS_FUNC(__VA_ARGS__))

#endif // CSYNTH_PLAYER_RUN_H
