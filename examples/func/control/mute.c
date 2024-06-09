//usr/bin/gcc "$0" -o bin/mute -Wall -Wextra -O3 -lm -lportaudio && ./bin/mute "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // press space to mute note
    func note = mute(' ', sine(C4));
    return play(mul_(note, .5));
}
