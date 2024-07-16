//usr/bin/gcc "$0" -o bin/sin -Wall -Wextra -O3 -lm -lportaudio && ./bin/sin "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // emulate sine wave with a timer
    func note = sin_op(mul_(200, timer(EvalParamPitchTick)));
    return play(note);
}
