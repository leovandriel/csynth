//usr/bin/gcc "$0" -o bin/simple_fm -Wall -Wextra -O3 -lm -lportaudio && ./bin/simple_fm "$@"; exit $?
// Based on: https://supercollider.github.io/examples
#include "../../src/func/all.h"
#include "../../src/run/play.h"

int main(void)
{
    func simple_fm = mul_(.5, add(
                                  mul_(.3, sine(kr_range_(100, 2e3, sine_(3)))),
                                  mul_(.3, sine(kr_range_(100, 2e3, sine_(1))))));
    return play(simple_fm);
}