//usr/bin/gcc "$0" -o bin/banks -Wall -Wextra -O3 -lm -lportaudio && ./bin/banks "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    func note = seq_loop_(.25, bdrum(), hihat(), snare(), hihat());
    return play(note);
}
