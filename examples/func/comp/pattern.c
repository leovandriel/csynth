//usr/bin/gcc "$0" -o bin/pattern -Wall -Wextra -O3 -lm -lportaudio && ./bin/pattern "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // TODO(leo): Implement
    func note = hush(sine(C4));
    return play(note);
}
