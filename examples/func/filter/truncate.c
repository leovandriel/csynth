//usr/bin/gcc "$0" -o bin/truncate -Wall -Wextra -O3 -lm -lportaudio && ./bin/truncate "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/player.h"

int main()
{
    // note at increasing intervals, triggering truncation, after which the note
    // is no longer generated
    func tone = sine(A4);
    func note = rect_(0, .1, tone);
    func length = linear_env_(1, .4, .8);
    func looped = loop(length, note);
    func truncated = truncate_(1, looped);
    return play(mul_(.5, truncated));
}
