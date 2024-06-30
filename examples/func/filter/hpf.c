//usr/bin/gcc "$0" -o bin/hpf -Wall -Wextra -O3 -lm -lportaudio && ./bin/hpf "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // high-pass filter with exponentially increasing frequency
    func note = hpf(saw(C4), expo(linear_env_(4, 0, 10)));
    return play(mul_(.1, note));
}
