//usr/bin/gcc "$0" -o bin/pause -Wall -Wextra -O3 -lm -lportaudio && ./bin/pause "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // press space to pause/play
    func note = pause_play(' ', sine(mul(C4, sine_(.1))));
    return play(note);
}
