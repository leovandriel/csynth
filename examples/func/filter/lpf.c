//usr/bin/gcc "$0" -o bin/lpf -Wall -Wextra -O3 -lm -lportaudio && ./bin/lpf "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // low-pass filter with exponentially decreasing frequency
    func note = lpf(expo(linear_env_(4, 10, 0)), mul_(.3, saw(C4)));
    return play(note);
}
