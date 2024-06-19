//usr/bin/gcc "$0" -o bin/lpf -Wall -Wextra -O3 -lm -lportaudio && ./bin/lpf "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // low-pass filter with exponentially decreasing frequency
    func note = lpf(saw(C4), expo(linear_env_(10, 0, 4)));
    return play(mul_(note, .1));
}
