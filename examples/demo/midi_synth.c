//usr/bin/gcc "$0" -o bin/midi_synth -Wall -Wextra -O3 -lm -lportaudio -lportmidi && ./bin/midi_synth "$@"; exit $?
#include "../../src/func/all.h"
#include "../../src/io/midi_player.h"

func note(func frequency)
{
    return unison(frequency, saw, 5, 0.01);
}

int main()
{
    func lpf_knob = display(knob_ex_(1, 70, 40000, 1), "lpf");
    func hpf_knob = display(knob_ex_(1, 71, 1, 40000), "hpf");
    func distortion_knob = display(knob_(1, 72, 0, 10), "distort");
    func pitch_knob = display(knob_ex_(1, 73, 0.1, 10), "pitch");
    func reverb_time = display(knob_(1, 75, 0, .5), "rev-time");
    func reverb_decay = display(knob_(1, 76, 0, .99), "rev-decay");
    func post_gain = display(knob_(1, 77, 1, 10), "gain");
    func keys = midi_keyboard(1, key, note, C0);
    func keys_filtered = mul(reverb(pitch(pitch_knob, lpf(hpf(distortion(keys, distortion_knob), hpf_knob), lpf_knob)), reverb_time, reverb_decay), post_gain);
    func drums = add(pad(10, 40, snare()), pad(10, 41, bdrum()), pad(10, 42, hihat()));
    return play_midi(add(mul_(keys_filtered, .2), drums));
}
