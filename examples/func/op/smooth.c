//usr/bin/gcc "$0" -o bin/smooth -Wall -Wextra -O3 -lm -lportaudio && ./bin/smooth "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // TODO: Implement
    func f = hush(sine(C4));
    return play(mul_(f, .5));
}
