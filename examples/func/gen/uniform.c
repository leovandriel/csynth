//usr/bin/gcc "$0" -o bin/uniform -Wall -Wextra -O3 -lm -lportaudio && ./bin/uniform "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // white noise
    func f = uniform();
    return play(mul_(f, .2));
}
