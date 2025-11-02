//usr/bin/gcc "$0" -o bin/biquad -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/biquad "$@"; exit $?
#include "../../../src/func/all.h"
#include "../../../src/run/midi_run.h"

int main(void)
{
    // white noise through a band-pass filter with midi knob for frequency and qfactor
    func frequency = gauge("frequency", knob_ex_(1, 70, 20000, 1));
    func qfactor = gauge("qfactor", knob_ex_(1, 71, .001, 100));
    func tone = bandpass(frequency, qfactor, white());
    return play_midi(mul_(.5, tone));
}
