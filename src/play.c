#include "./example/all.h"
#include "./util/player.h"

int main(int argc, char **argv)
{
    const char *name = argc > 1 ? argv[1] : NULL;
    double length = 0;
    func f = all_examples(name, &length);
    play(f, length);
    return 0;
}
