//usr/bin/gcc "$0" -o bin/timer -Wall -Wextra -O3 -lm -lportaudio && ./bin/timer "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // play frequency that increases 100 Hz every second
    func note = sine(pitch_timer_(100));
    return play(note);
}
