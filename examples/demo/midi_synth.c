//usr/bin/gcc "$0" -o bin/midi_synth -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/midi_synth "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/midi_player.h"

int main()
{
    func lpf_knob = gauge("lpf", knob_ex_(1, 70, 40000, 1));
    func hpf_knob = gauge("hpf", knob_ex_(1, 71, 1, 40000));
    func distortion_knob = gauge("distort", knob_(1, 72, 0, 10));
    func overtone_knob = gauge("overtone", knob_(1, 73, -10, 1));
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
    synth = hpf(hpf_knob, synth);
    synth = lpf(lpf_knob, synth);
    synth = reverb(reverb_time, reverb_decay, synth);
    synth = mul(post_gain, synth);
    func drums = add(pad(10, 40, snare()), pad(10, 41, bdrum()), pad(10, 42, hihat()));
    return play_midi(fps("fps", add(mul_(.2, synth), drums)));
}
