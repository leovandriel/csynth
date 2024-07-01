//usr/bin/gcc "$0" -o bin/looper -Wall -Wextra -O3 -lm -lportaudio && ./bin/looper "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // looping keyboard
    display_keyboard(' ', "recording");
    func keys = keyboard(trigger, decay_(.5, sine(C4)));
    func fun = avg(
        looper_('1', 2, keys),
        looper_('2', 2, keys),
        looper_('3', 2, keys),
        looper_('4', 2, keys));
    return play(fun);
}
