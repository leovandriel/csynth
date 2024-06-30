//usr/bin/gcc "$0" -o bin/distortion -Wall -Wextra -O3 -lm -lportaudio && ./bin/distortion "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // distortion filter with oscillating shape
    func note = distortion(mul_(10, sine_(.3)), sine(C4));
    return play(mul_(.1, note));
}
