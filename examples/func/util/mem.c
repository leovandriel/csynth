//usr/bin/gcc "$0" -o bin/mem -Wall -Wextra -O3 -lm -lportaudio -DALLOC_TRACE && ./bin/mem "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // display amount of memory allocated and freed
    func note = sine(C4);
    return play(mem(note));
}
