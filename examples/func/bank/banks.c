//usr/bin/gcc "$0" -o bin/banks -Wall -Wextra -O3 -lm -lportaudio && ./bin/banks "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    func note = loop_(2, seq_fix_(.5, bdrum(), hihat(), snare(), hihat()));
    return play(note);
}
