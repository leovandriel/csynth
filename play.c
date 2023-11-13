//usr/bin/gcc "$0" -o bin/play -Wall -Wextra -O3 -lm -lportaudio && ./bin/play "$@"; exit $?
#include "./src/example/all.h"
#include "./src/util/player.h"

int main(int argc, char **argv)
{
    const char *name = argc > 1 ? argv[1] : NULL;
    double length = 0;
    func f = all_examples(name, &length);
    play(f, 2);
    return 0;
}
