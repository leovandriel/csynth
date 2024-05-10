//usr/bin/gcc "$0" -o bin/keyboard -Wall -Wextra -O3 -lm -lportaudio && ./bin/keyboard "$@"; exit $?
#include "../src/func/all.h"
#include "../src/util/player.h"
#include "../src/util/display.h"

func note(func frequency)
{
    return low_pass(karplus_strong(frequency, _(.3)), frequency);
}

int main()
{
    func hihat = mul(high_pass_(uniform(), 20000), decay_(.05));
    func snare = mul(uniform(), decay_(.05));
    func bdrum = mul(sine(linear_(60, 30, 1)), decay_(.05), _(3));
    func tempo = knob_rel('1', .5, -.1);
    func loops = add(
        mute('Q', loop(hihat, mul_(tempo, .5))),
        mute('W', loop(delay(snare, mul_(tempo, 1)), mul_(tempo, 2))),
        mute('E', loop(bdrum, mul_(tempo, 2))));
    func drums = add(
        press('q', hihat),
        press('w', snare),
        press('e', bdrum));
    func guitar = add(
        press('z', note(C4)),
        press('s', note(Cs4)),
        press('x', note(D4)),
        press('d', note(Eb4)),
        press('c', note(E4)),
        press('v', note(F4)),
        press('g', note(Fs4)),
        press('b', note(G4)),
        press('h', note(Ab4)),
        press('n', note(A4)),
        press('j', note(Bb4)),
        press('m', note(B4)),
        press(',', note(C5)),
        press('l', note(Cs5)),
        press('.', note(D5)),
        press(';', note(Eb5)),
        press('/', note(E5)));
    display_add_label(' ', "play");
    display_add_label('1', "1:tempo");
    display_add_label('Q', "Q:hihat");
    display_add_label('W', "W:snare");
    display_add_label('E', "E:bdrum");
    return play(add(mul_(loops, 0.5), drums, guitar));
}
