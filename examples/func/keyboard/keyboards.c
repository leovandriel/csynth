//usr/bin/gcc "$0" -o bin/keyboards -Wall -Wextra -O3 -lm -lportaudio && ./bin/keyboards "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // TODO(leo): Implement
    func note = hush(sine(C4));
    return play(mul_(note, .5));
}