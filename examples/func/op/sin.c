//usr/bin/gcc "$0" -o bin/sin -Wall -Wextra -O3 -lm -lportaudio && ./bin/sin "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // emulate sine wave with a timer
    func note = sin_op(pitch_timer_(2000));
    return play(note);
}
