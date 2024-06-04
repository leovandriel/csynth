//usr/bin/gcc "$0" -o bin/notes -Wall -Wextra -O3 -lm -lportaudio && ./bin/notes "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // play C, D, E, C5
    func f = seq_fix_(1, saw(C4), saw(D4), saw(E4), saw(C5));
    return play_(mul_(f, .1), 4);
}