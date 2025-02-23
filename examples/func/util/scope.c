//usr/bin/gcc "$0" -o bin/scope -Wall -Wextra -O3 -lm -lportaudio -lSDL2 && ./bin/scope "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/screen_player.h"

int main(void)
{
    RenderPipe pipe = {.width = 400, .height = 400};
    func fm = sine(kr_range(C4, C5, sine_(0.5)));
    func scoped = scope(fm, C4, &pipe);
    return play_screen(scoped, &pipe);
}
