//usr/bin/gcc "$0" -o bin/keyboard -Wall -Wextra -O3 -lm -lportaudio && ./bin/keyboard "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    func tone = decay_(.3, sine(C4));
    func synth = keyboard(trigger, tone);
    return play(synth);
}
