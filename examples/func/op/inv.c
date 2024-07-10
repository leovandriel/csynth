//usr/bin/gcc "$0" -o bin/inv -Wall -Wextra -O3 -lm -lportaudio && ./bin/inv "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // Fade asympotically to zero
    func note = mul(sine(C4), inv(pitch_timer_(10)));
    return play(note);
}
