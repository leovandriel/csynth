//usr/bin/gcc "$0" -o bin/trigger -Wall -Wextra -O3 -lm -lportaudio && ./bin/trigger "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // press space to trigger note
    func note = trigger(' ', decay_(.5, sine(C4)));
    return play(mul_(0.5, note));
}
