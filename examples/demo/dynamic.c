//usr/bin/gcc "$0" -o bin/dynamic -Wall -Wextra -O3 -lm -lportaudio && ./bin/dynamic "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

#define P(_f) (mul(_f, pitch))
#define T(_f) (dvd(_(_f), speed))

static func beep_dynamic(func pitch, func speed)
{
    func tone = sine(P(A4));
    func note = mul(rect(T(0), T(.3), tone), _(.5));
    func looped = loop(T(1.5), note);
    func revved = reverb(T(.4), _(.2), looped);
    return revved;
}

func wobble_both()
{
    func wobble = continuous(add_(1, mul_(.1, sine_(.1))));
    return beep_dynamic(wobble, wobble);
}

func modulate_pitch()
{
    func modulate = continuous(add_(.01, mul_(.5, timer(EvalParamPitchTick))));
    return beep_dynamic(modulate, ONE);
}

func modulate_speed()
{
    func modulate = continuous(add_(.01, mul_(.5, timer(EvalParamPitchTick))));
    return beep_dynamic(ONE, modulate);
}

int main()
{
    func dynamic = seq_rel(
        modulate_pitch(), _(10),
        modulate_speed(), _(10),
        wobble_both(), _(10));
    return play(dynamic);
}
