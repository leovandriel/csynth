//usr/bin/gcc "$0" -o bin/finish -Wall -Wextra -O3 -lm -lportaudio && ./bin/finish "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/io/term_player.h"

int main(void)
{
    // note at increasing intervals, triggering truncation, after which the note
    // is no longer generated
    func tone = sine(A4);
    func note = rect_(0, .1, tone);
    func length = linear_env_(1, .4, .8);
    func looped = loop(length, note);
    func finished = finish_(1, looped);
    return play(finished);
}
