//usr/bin/gcc "$0" -o bin/hpf -Wall -Wextra -O3 -lm -lportaudio && ./bin/hpf "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // high-pass filter with exponentially increasing frequency
    func note = hpf(expo(linear_env_(4, 0, 10)), mul_(.3, saw(C4)));
    return play(note);
}
