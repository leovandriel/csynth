//usr/bin/gcc "$0" -o bin/beep -Wall -Wextra -O3 -lm -lportaudio && ./bin/beep "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

int main()
{
    func tone = sine(A4);
    func note = mul(rect_(0, .3, tone), _(.5));
    func looped = loop_(1.5, note);
    func revved = reverb_(.4, .2, looped);
    return play(revved);
}
