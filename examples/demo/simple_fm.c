//usr/bin/true && ./utils/run.c "$0" -Wall -Wextra -O3 -lm -lportaudio; exit $?
// Based on: https://supercollider.github.io/examples
#include "../../src/func/all.h"
#include "../../src/io/player.h"

int main(void)
{
    func simple_fm = mul_(.5, add(
                                  mul_(.3, sine(kr_range_(100, 2e3, sine_(3)))),
                                  mul_(.3, sine(kr_range_(100, 2e3, sine_(1))))));
    return play(simple_fm);
}