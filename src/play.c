#include "./example/all.h"
#include "./core/player.h"

int main(int argc, char **argv)
{
    const char *name = argc > 1 ? argv[1] : NULL;
    double length = 0;
    play(all_examples(name, &length), length);
    return 0;
}
