//usr/bin/gcc "$0" -o bin/dynamic -Wall -Wextra -O3 -lm -lportaudio && ./bin/dynamic "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/run/play.h"

static func beep(void)
{
    func tone = sine(A4);
    func note = mul_(.5, rect_(0, .3, tone));
    func looped = loop_(1.5, note);
    func revved = reverb_(.4, .2, looped);
    return revved;
}

func modulate_pitch(void)
{
    func modulate = continuous(add_(.01, mul_(.5, timer(EvalParamPitchTick))));
    return pitch(modulate, beep());
}

func modulate_tempo(void)
{
    func modulate = continuous(add_(.01, mul_(.5, timer(EvalParamPitchTick))));
    return tempo(modulate, beep());
}

/** @brief Demo modulation of pitch and tempo.
 *
 * The demo modulates the pitch and tempo of a sine wave.
 * It also demonstrates the use of a timer to control playback duration.
 */
int main(void)
{
    func dynamic = seq_rel(
        modulate_pitch(), _(10),
        modulate_tempo(), _(10));
    return play_time(10, dynamic);
}
