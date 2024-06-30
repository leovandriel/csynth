//usr/bin/gcc "$0" -o bin/track -Wall -Wextra -O3 -lm -lportaudio && ./bin/track "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // TODO(leo): Implement
    func note = hush(sine(C4));
    return play(mul_(0.5, note));
}
