//usr/bin/gcc "$0" -o bin/comps -Wall -Wextra -O3 -lm -lportaudio && ./bin/comps "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // TODO(leo): Implement
    func note = hush(sine(C4));
    return play(note);
}
