//usr/bin/gcc "$0" -o bin/scope -Wall -Wextra -O3 -lm -lportaudio && ./bin/scope "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    func note = scope(circle(C4), C4);
    return play(note);
}
