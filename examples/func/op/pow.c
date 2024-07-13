//usr/bin/gcc "$0" -o bin/pow -Wall -Wextra -O3 -lm -lportaudio && ./bin/pow "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // Exponential increase in frequency
    func note = sine(pow_op(C4, timer(EvalParamPitchTick)));
    return play(note);
}
