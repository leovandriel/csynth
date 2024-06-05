//usr/bin/gcc "$0" -o bin/max -Wall -Wextra -O3 -lm -lportaudio && ./bin/max "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // TODO: Implement
    func f = hush(sine(C4));
    return play(mul_(f, .5));
}
