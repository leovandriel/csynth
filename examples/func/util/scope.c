//usr/bin/gcc "$0" -o bin/scope -Wall -Wextra -O3 -lm -lportaudio -lSDL2 && ./bin/scope "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/screen_run.h"

int main(void)
{
    func fm = sine(kr_range(C4, C5, sine_(0.1)));
    RenderPipe pipe = {.width = 400, .height = 400};
    func scoped = scope(NULL, &pipe, fm);
    return play_screen(scoped, &pipe);
}
