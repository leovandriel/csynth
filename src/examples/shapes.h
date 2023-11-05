#include "../core/funcs.h"

func shapes()
{
    func all = comp(
        mul(sine(A4), _(.5)), _(0.3), ZERO, _(0.2),
        mul(triangle(A4), _(.5)), _(0.3), ZERO, _(0.2),
        mul(square(A4), _(.25)), _(0.3), ZERO, _(0.2),
        mul(saw(A4), _(.25)), _(0.3), ZERO, _(0.2));
    func looped = loop(all, _(2));
    func scaled = mul(looped, _(.1));
    return scaled;
}
