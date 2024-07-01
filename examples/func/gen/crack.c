//usr/bin/gcc "$0" -o bin/crack -Wall -Wextra -O3 -lm -lportaudio && ./bin/crack "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // random crackling at 1 and 10 Hz (times per second, on average)
    func fun = seq_rel(
        print("crack(1)", crack_(1)), _(4),
        print("crack(10)", crack_(10)), _(4),
        print("crack(100)", crack_(100)), _(4));
    return play_duration(12, mul_(.5, fun));
}
