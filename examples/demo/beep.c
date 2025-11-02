//usr/bin/gcc "$0" -o bin/beep -Wall -Wextra -O3 -lm -lportaudio && ./bin/beep "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/run/play.h"

int main(void)
{
    func tone = sine(A4);
    func note = mul_(.5, rect_(0, .3, tone));
    func looped = loop_(1.5, note);
    func revved = reverb_(.4, .2, looped);
    return play(revved);
}
