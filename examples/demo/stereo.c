//usr/bin/gcc "$0" -o bin/stereo -Wall -Wextra -O3 -lm -lportaudio && ./bin/stereo "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

static float deg2rad = M_PI / 180;

func ear(func angle)
{
    return mul_(.3, add_(1.1, sin_op(mul_(deg2rad, angle))));
}

int main()
{
    func hihat_ = loop_(.25, hihat());
    func snare_ = loop_(1, delay_(.5, snare()));
    func bdrum_ = loop_(1, mul(bdrum(), _(3)));
    func angle = pitch_timer_(60);
    func left = add(
        mul(hihat_, ear(add_(0, angle))),
        mul(snare_, ear(add_(120, angle))),
        mul(bdrum_, ear(add_(240, angle))));
    func right = add(
        mul(hihat_, ear(add_(180, angle))),
        mul(snare_, ear(add_(300, angle))),
        mul(bdrum_, ear(add_(60, angle))));
    return play_stereo(left, right);
}
