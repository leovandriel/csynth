//usr/bin/gcc "$0" -o bin/prod -Wall -Wextra -O3 -lm -lportaudio && ./bin/prod "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // play frequency that increases exponentially
    func note = sine(prod_create(const_(1.00005)));
    return play(note);
}
