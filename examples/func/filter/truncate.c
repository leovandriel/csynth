//usr/bin/gcc "$0" -o bin/truncate -Wall -Wextra -O3 -lm -lportaudio && ./bin/truncate "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // note at increasing intervals, triggering truncation, after which the note
    // is no longer generated
    func tone = sine(A4);
    func note = rect_(tone, 0, .1);
    func length = linear_env_(.4, .8, 1);
    func looped = loop(note, length);
    func truncated = trunc_(looped);
    return play(mul_(truncated, .5));
}
