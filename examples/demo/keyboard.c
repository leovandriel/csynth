//usr/bin/gcc "$0" -o bin/keyboard -Wall -Wextra -O3 -lm -lportaudio && ./bin/keyboard "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"
#include "../../src/ui/display.h"

func note(func frequency)
{
    return lpf(karplus_strong_(frequency, .3), frequency);
}

int main()
{
    func hihat = decay_(hpf_(uniform(), 20000), .05);
    func snare = decay_(uniform(), .05);
    func bdrum = mul(decay_(sine(linear_env_(60, 30, 1)), .05), _(3));
    func tempo = stepper_rel('1', .5, -.1);
    func loops = add(
        mute('Q', loop(hihat, mul_(tempo, .5))),
        mute('W', loop(delay(snare, mul_(tempo, 1)), mul_(tempo, 2))),
        mute('E', loop(bdrum, mul_(tempo, 2))));
    func drums = add(
        trigger('q', hihat),
        trigger('w', snare),
        trigger('e', bdrum));
    func guitar = keyboard(trigger, note, C4);
    display('\t', "play");
    display('1', "1:tempo");
    display('Q', "Q:hihat");
    display('W', "W:snare");
    display('E', "E:bdrum");
    return play(add(mul_(loops, 0.5), drums, guitar));
}
