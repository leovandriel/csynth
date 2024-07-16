//usr/bin/gcc "$0" -o bin/record -Wall -Wextra -O3 -lm -lportaudio && ./bin/record "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // record the keyboard output
    func fun = keyboard(trigger, decay_(.3, sine(C4)));
    func recorded = record("output/record.wav", fun);
    return play(recorded);
}
