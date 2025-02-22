//usr/bin/gcc "$0" -o bin/mute -Wall -Wextra -O3 -lm -lportaudio && ./bin/mute "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // press space to mute note
    func note = mute(' ', sine(C4));
    return play(note);
}
