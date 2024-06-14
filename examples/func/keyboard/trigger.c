//usr/bin/gcc "$0" -o bin/trigger -Wall -Wextra -O3 -lm -lportaudio && ./bin/trigger "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // press space to trigger note
    func note = trigger(' ', decay_(sine(C4), .5));
    return play(mul_(note, .5));
}
