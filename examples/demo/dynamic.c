//usr/bin/gcc "$0" -o bin/dynamic -Wall -Wextra -O3 -lm -lportaudio && ./bin/dynamic "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/player.h"

static func beep()
{
    func tone = sine(A4);
    func note = mul_(.5, rect_(0, .3, tone));
    func looped = loop_(1.5, note);
    func revved = reverb_(.4, .2, looped);
    return revved;
}

func modulate_pitch()
{
    func modulate = continuous(add_(.01, mul_(.5, timer(EvalParamPitchTick))));
    return pitch(modulate, beep());
}

func modulate_tempo()
{
    func modulate = continuous(add_(.01, mul_(.5, timer(EvalParamPitchTick))));
    return tempo(modulate, beep());
}

int main()
{
    func dynamic = seq_rel(
        modulate_pitch(), _(10),
        modulate_tempo(), _(10));
    return play_duration(20, dynamic);
}
