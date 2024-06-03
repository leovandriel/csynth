//usr/bin/gcc "$0" -o bin/simple_fm -Wall -Wextra -O3 -lm -lportaudio && ./bin/simple_fm "$@"; exit $?
// Based on: https://supercollider.github.io/examples
#include "../../src/func/all.h"
#include "../../src/io/player.h"

int main()
{
    func simple_fm = mul_(add(
                              mul_(sine(kr_range_(sine_(3), 100, 2e3)), .3),
                              mul_(sine(kr_range_(sine_(1), 100, 2e3)), .3)),
                          .5);
    return play(simple_fm);
}