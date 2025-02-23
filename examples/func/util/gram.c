//usr/bin/gcc "$0" -o bin/gram -Wall -Wextra -O3 -lm -lportaudio -lSDL2 && ./bin/gram "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/screen_player.h"

int main(void)
{
    RenderPipe pipe = {.width = 400, .height = 400};
    func fm = sine(kr_range(C4, C5, sine_(0.5)));
    func note = gram(fm, &pipe);
    return play_screen(note, &pipe);
}
