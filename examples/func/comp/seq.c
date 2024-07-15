//usr/bin/gcc "$0" -o bin/seq -Wall -Wextra -O3 -lm -lportaudio && ./bin/seq "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    func melody = seq_loop_(2,
                            seq_loop_(.25, C3, C4),
                            seq_loop_(.25, Bb2, Bb3),
                            seq_loop_(.25, F3, F4),
                            seq_loop_(.25, Eb3, Eb4));
    func fun = mul_(.1, lowpass_(400, 1, saw(melody)));
    return play_duration(16, fun);
}
