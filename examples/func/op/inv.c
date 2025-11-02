//usr/bin/gcc "$0" -o bin/inv -Wall -Wextra -O3 -lm -lportaudio && ./bin/inv "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/play.h"

int main(void)
{
    // Fade asympotically to zero
    func note = mul(sine(C4), _(0.1), inv(timer(EvalParamPitchTick)));
    return play(note);
}
