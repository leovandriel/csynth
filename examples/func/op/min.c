//usr/bin/gcc "$0" -o bin/min -Wall -Wextra -O3 -lm -lportaudio && ./bin/min "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // Linear increase with maximum value
    func note = mul(sine(C4), min_(0.5, timer(EvalParamPitchTick)));
    return play(note);
}
