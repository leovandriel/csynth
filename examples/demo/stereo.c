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
    func hihat_ = loop_(hihat(), .25);
    func snare_ = loop_(delay_(snare(), .5), 1);
    func bdrum_ = loop_(mul(bdrum(), _(3)), 1);
    func angle = mul_(timer(), 60);
    func left = add(
        mul(hihat_, ear(add_(angle, 0))),
        mul(snare_, ear(add_(angle, 120))),
        mul(bdrum_, ear(add_(angle, 240))));
    func right = add(
        mul(hihat_, ear(add_(angle, 180))),
        mul(snare_, ear(add_(angle, 300))),
        mul(bdrum_, ear(add_(angle, 60))));
    return play_stereo(left, right);
}
