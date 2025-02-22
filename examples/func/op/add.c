//usr/bin/gcc "$0" -o bin/add -Wall -Wextra -O3 -lm -lportaudio && ./bin/add "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // Mix two notes
    func note = add(sine(C4), sine(E4));
    return play(note);
}
