//usr/bin/gcc "$0" -o bin/midi_synth -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/midi_synth "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/run/midi_run.h"
#include "../../src/run/play.h"
#include "../../src/util/func_tools.h"

int main(void)
{
    func lpf_knob = gauge("lpf", knob_ex_(1, 70, 20000, 1));
    // func_print(lpf_knob);
    func hpf_knob = gauge("hpf", knob_ex_(1, 71, 1, 20000));
    func distortion_knob = gauge("distort", knob_(1, 72, 0, 2));
    func overtone_knob = gauge("overtone", knob_(1, 73, -10, 0));
    func detune_knob = gauge("detune", knob_ex_(1, 74, .001, 1.0));
    func reverb_time = gauge("rev-time", knob_(1, 75, 0, .5));
    func reverb_decay = gauge("rev-decay", knob_ex_(1, 76, .01, .99));
    func post_gain = gauge("gain", knob_(1, 77, 1, 10));
    func note = saw(C0);
    note = unison(5, detune_knob, note);
    note = overtone(-4, overtone_knob, note);
    func synth = midi_keyboard(1, note);
    synth = bend_(1, 1.06, synth);
    synth = distortion(distortion_knob, synth);
    synth = highpass(hpf_knob, _(1), synth);
    synth = lowpass(lpf_knob, _(1), synth);
    synth = reverb(reverb_time, reverb_decay, synth);
    synth = mul(post_gain, synth);
    func drums = add(pad(10, 40, snare()), pad(10, 41, bdrum()), pad(10, 42, hihat()));
    return play(fps("fps", add(mul_(.2, synth), mul_(5, drums))), midi_run());
}
