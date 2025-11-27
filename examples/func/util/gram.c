//usr/bin/gcc "$0" -o bin/gram -Wall -Wextra -O3 -lm -lportaudio -lSDL2 && ./bin/gram "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/screen_run.h"

int main(void)
{
    // func fm = sine(kr_range(C3, C9, sine_(0.5)));
    func fm = pitch_shift(kr_range_(0, 6, sine_(0.5)), sine(C3));
    RenderPipe pipe = {.width = 400, .height = 400};
    func note = gram(fm, &pipe);
    return play_screen(note, &pipe);
}
