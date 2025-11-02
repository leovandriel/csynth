//usr/bin/gcc "$0" -o bin/sum -Wall -Wextra -O3 -lm -lportaudio && ./bin/sum "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // play frequency that increases 100 Hz every second
    func note = sine(mul_(100, timer(EvalParamPitchTick)));
    return play(note);
}
