//usr/bin/gcc "$0" -o bin/max -Wall -Wextra -O3 -lm -lportaudio && ./bin/max "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // Linear fade with minimum value
    func note = mul(sine(C4), max_(0.1, sub(ONE, timer(EvalParamPitchTick))));
    return play(note);
}
