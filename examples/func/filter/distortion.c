//usr/bin/gcc "$0" -o bin/distortion -Wall -Wextra -O3 -lm -lportaudio && ./bin/distortion "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // distortion filter with oscillating shape
    func note = mul_(.5, distortion(mul_(10, sine_(.3)), sine(C4)));
    return play(note);
}
