//usr/bin/gcc "$0" -o bin/banks -Wall -Wextra -O3 -lm -lportaudio && ./bin/banks "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    func note = loop_(1, tempo_(4, seq_fix(bdrum(), hihat(), snare(), hihat())));
    return play(note);
}
