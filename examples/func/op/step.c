//usr/bin/gcc "$0" -o bin/step -Wall -Wextra -O3 -lm -lportaudio && ./bin/step "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // Step function
    func note = step_(0.5, sine(C4));
    return play(note);
}
