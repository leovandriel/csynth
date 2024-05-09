//usr/bin/gcc "$0" -o bin/keyboard -Wall -Wextra -O3 -lm -lportaudio && ./bin/keyboard "$@"; exit $?
#include "../src/func/all.h"
#include "../src/util/player.h"

int main()
{
    func hihat = mul(high_pass_(uniform(), 20000), decay_(.05));
    func snare = mul(uniform(), decay_(.05));
    func bdrum = mul(sine(linear_(60, 30, 1)), decay_(.05), _(3));
    func loops = add(
        mute('q', loop_(hihat, .5)),
        mute('w', loop_(delay_(snare, 1), 2)),
        mute('e', loop_(bdrum, 2)));
    func keyboard = add(
        press('a', hihat),
        press('s', snare),
        press('d', bdrum));
    printf("Usage: [a] hihat, [s] snare, [d] bdrum, [q/w/e] loop on/off\r");
    return play(mul_(add(loops, keyboard), .4));
}
