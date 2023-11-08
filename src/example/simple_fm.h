// Based on: https://supercollider.github.io/examples
#include "../func/all.h"

func simple_fm()
{
    return mul_(add(
                    mul_(sine(kr_range_(sine_(3), 100, 2e3)), .3),
                    mul_(sine(kr_range_(sine_(1), 100, 2e3)), .3)),
                .5);
}