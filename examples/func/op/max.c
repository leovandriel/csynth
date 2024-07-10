//usr/bin/gcc "$0" -o bin/max -Wall -Wextra -O3 -lm -lportaudio && ./bin/max "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // Linear fade with minimum value
    func note = mul(sine(C4), max_(0.1, sub(ONE, pitch_timer_(1.0))));
    return play(note);
}
