//usr/bin/gcc "$0" -o bin/mem -Wall -Wextra -O3 -lm -lportaudio && ./bin/mem "$@"; exit $?
#define ALLOC_TRACE
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main(void)
{
    // display amount of memory allocated and freed
    func note = sine(C4);
    return play(mem(note));
}
