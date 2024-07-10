//usr/bin/gcc "$0" -o bin/min -Wall -Wextra -O3 -lm -lportaudio && ./bin/min "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // Linear increase with maximum value
    func note = mul(sine(C4), min_(0.5, pitch_timer_(1.0)));
    return play(note);
}
