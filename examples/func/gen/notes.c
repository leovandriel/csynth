//usr/bin/gcc "$0" -o bin/notes -Wall -Wextra -O3 -lm -lportaudio && ./bin/notes "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // play C, D, E, C5
    func fun = tempo_(2, saw(seq_fix(C4, D4, E4, C5)));
    return play_duration(2, mul_(.1, fun));
}
