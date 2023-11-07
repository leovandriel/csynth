#include "../func/all.h"

func shapes()
{
    func all = comp_rel(
        mul_(sine(A4), .5), _(0.3), ZERO, _(0.2),
        mul_(triangle(A4), .5), _(0.3), ZERO, _(0.2),
        mul_(square(A4), .25), _(0.3), ZERO, _(0.2),
        mul_(saw(A4), .25), _(0.3), ZERO, _(0.2));
    func looped = loop_(all, 2);
    func scaled = mul_(looped, .1);
    return scaled;
}
