//usr/bin/gcc "$0" -o bin/drums -Wall -Wextra -O3 -lm -lportaudio && ./bin/drums "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    func note = loop_(seq_fix_(.5, bdrum(), hihat(), snare(), hihat()), 2);
    return play(mul_(note, .5));
}
