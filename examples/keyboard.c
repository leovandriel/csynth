//usr/bin/gcc "$0" -o bin/keyboard -Wall -Wextra -O3 -lm -lportaudio && ./bin/keyboard "$@"; exit $?
#include "../src/func/all.h"
#include "../src/util/player.h"

int main()
{
    func snare = mul(uniform(), decay_(.05));
    func bdrum = mul(sine(linear_(60, 30, 1)), decay_(.05), _(3));
    func hihat = mul(high_pass_(uniform(), 20000), decay_(.05));
    func keyboard = add(
        press('a', snare),
        press('s', bdrum),
        press('d', hihat));
    return play(mul_(keyboard, .4));
}
