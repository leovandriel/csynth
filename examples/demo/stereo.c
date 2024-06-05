//usr/bin/gcc "$0" -o bin/stereo -Wall -Wextra -O3 -lm -lportaudio && ./bin/stereo "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

static float deg2rad = M_PI / 180;

func ear(func angle)
{
    return mul_(add_(sin_op(mul_(angle, deg2rad)), 1.1), 0.3);
}

int main()
{
    func hihat = loop_(decay_(hpf_(uniform(), 20000), .05), .25);
    func snare = loop_(delay_(decay_(uniform(), .05), .5), 1);
    func bdrum = loop_(mul(decay_(sine(linear_env_(60, 30, 1)), .05), _(3)), 1);
    func angle = mul_(timer(), 60);
    func left = add(
        mul(hihat, ear(add_(angle, 0))),
        mul(snare, ear(add_(angle, 120))),
        mul(bdrum, ear(add_(angle, 240))));
    func right = add(
        mul(hihat, ear(add_(angle, 180))),
        mul(snare, ear(add_(angle, 300))),
        mul(bdrum, ear(add_(angle, 60))));
    return play_stereo(left, right);
}
