//usr/bin/gcc "$0" -o bin/distortion -Wall -Wextra -O3 -lm -lportaudio && ./bin/distortion "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // distortion filter with oscillating shape
    func note = distortion(sine(C4), mul_(sine_(.3), 10));
    return play(mul_(note, .1));
}
