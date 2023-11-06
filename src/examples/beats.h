#include "../core/funcs.h"

func beats()
{
    func base = mul(sine(A1), hump_(0, 0.01, .05, .1), _(2));
    func hat = mul(add(saw(A5), noise()), hump_(0, 0.005, 0.005, .01), _(.5));
    func base_line = comp(
        base, _(1.25), base, _(.75),
        base, _(1.25), base, _(.5), base, _(.25),
        base, _(1.25), base, _(.75),
        base, _(1.25), base, _(.5), base, _(.12), base, _(.13));
    func hat_line = comp(
        ZERO, _(.5), hat, _(1), hat, _(.5),
        ZERO, _(.5), hat, _(1), hat, _(.5),
        ZERO, _(.5), hat, _(1), hat, _(.25), hat, _(.12), hat, _(.13),
        ZERO, _(.5), hat, _(1), hat, _(.5));
    func low_line = comp(
        mul(sine(A1), hump_(0, 0.05, 1.95, 2), _(8)), _(2),
        mul(sine(E2), hump_(0, 0.05, .7, .75), _(8)), _(.75),
        mul(sine(D2), hump_(0, 0.05, .7, .75), _(8)), _(.75),
        mul(sine(E2), hump_(0, 0.05, .45, .5), _(8)), _(.5),
        mul(sine(A2), hump_(0, 0.05, 1.95, 2), _(8)), _(2),
        mul(sine(E2), hump_(0, 0.05, 1.95, 2), _(8)), _(2));
    func composition = add(base_line, hat_line, low_line);
    func looped = loop(composition, _(8));
    func scaled = mul(looped, _(.1));
    return scaled;
}
