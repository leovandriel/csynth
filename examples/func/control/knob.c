//usr/bin/gcc "$0" -o bin/knob -Wall -Wextra -O3 -lm -lportaudio && ./bin/knob "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // press space, followed by up/down to change frequency wit 10 HZ
    func note = sine(knob(' ', C4_, 10));
    return play(mul_(note, .5));
}
