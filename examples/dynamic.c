//usr/bin/gcc "$0" -o bin/dynamic -Wall -Wextra -O3 -lm -lportaudio && ./bin/dynamic "$@"; exit $?
#include "../src/func/all.h"
#include "../src/util/player.h"

#define P(_f) (mul(_f, pitch))
#define T(_f) (dvd(_(_f), speed))

static func beep_dynamic(func pitch, func speed)
{
    func tone = sine(P(A4));
    func note = mul(tone, block(T(0), T(.3)), _(.5));
    func looped = loop(note, T(1.5));
    func revved = reverb(looped, T(.4), _(.2));
    return revved;
}

func wobble_both()
{
    func wobble = continuous(add_(mul_(sine_(.1), .1), 1));
    return beep_dynamic(wobble, wobble);
}

func modulate_pitch()
{
    func modulate = continuous(add_(mul_(timer(), .5), .01));
    return beep_dynamic(modulate, ONE);
}

func modulate_speed()
{
    func modulate = continuous(add_(mul_(timer(), .5), .01));
    return beep_dynamic(ONE, modulate);
}

int main()
{
    func dynamic = comp_rel(
        modulate_pitch(), _(10),
        modulate_speed(), _(10),
        wobble_both(), _(10));
    return play(dynamic, 30);
}
